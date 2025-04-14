#include "service.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"
#include "../utils/freeMemory.h"
#include "../../modules/services.h"
#include "../../model/model_central.h"

// Hàm tải nội dung từ file text vào Liststore
static void load_file_txt_to_liststore(GtkListStore *store, const char *filename) {
    
    // Mở file
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Không mở được file: %s\n", filename);
        return;
    }

    // Tạo mảng line đọc từng hàng của file
    char line[256];

    // Dùng fgets đọc file đến khi hết dữ liệu thì dừng vòng lặp 
    while (fgets(line, sizeof(line), file)) {
        char id[10], name[100], cost[20];
        
        // Lưu các chuỗi trong file (với đúng định dạng) vào các mảng đã khai báo
        // %9[^|]: lưu tối đa 9 ký tự hoặc dừng lại khi gặp |
        // %49[^\n]: lưu tối đa 49 ký tự hoặc dừng lại khi gặp \n
        if (sscanf(line, "%9[^|]|%99[^|]|%19[^\n]", id, name, cost) == 3) {
            GtkTreeIter iter;

            // Thêm hàng trong Liststore
            gtk_list_store_append(store, &iter);
            // Lưu vào Liststore
            gtk_list_store_set(store, &iter, 
                              0, id, 
                              1, name, 
                              2, cost, 
                              -1);
        }
    }
    fclose(file);
}

static gboolean filter_visible_func(GtkTreeModel *model, GtkTreeIter *iter, gpointer data);

static void onSearchChanged(GtkSearchEntry *searchBar, GtkTreeView *listView)
{
    const gchar *search_text;
    GtkTreeModel *model;
    GtkTreeModelFilter *filter_model;

    // Get the original model
    model = gtk_tree_view_get_model(listView);

    // Check if the current model is already a filter model
    if (GTK_IS_TREE_MODEL_FILTER(model))
    {
        // Reuse model filter
        filter_model = GTK_TREE_MODEL_FILTER(model);
        // Take the original model from filter model
        model = gtk_tree_model_filter_get_model(filter_model);
    }
    else 
    {
        // If not model filter -> create a new one
        filter_model = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(model, NULL));
    }

    // Take text from searchBar
    search_text = gtk_entry_get_text(GTK_ENTRY(searchBar));

    // Chỉ cấp phát và cập nhật text tìm kiếm lại khi search_text thay đổi
    const gchar *old_text = g_object_get_data(G_OBJECT(filter_model), "search-text");
    if (g_strcmp0(old_text, search_text) != 0)
    {
        // Store search text as object data to use in filter function
        g_object_set_data_full(G_OBJECT(filter_model), "search-text",
                                                g_strdup(search_text), (GDestroyNotify)g_free);

    }

    // If model filter does not exist
    if (!GTK_IS_TREE_MODEL_FILTER(gtk_tree_view_get_model(listView)))
    {
        // Set visible function
        gtk_tree_model_filter_set_visible_func(filter_model,
            (GtkTreeModelFilterVisibleFunc)filter_visible_func, filter_model, NULL);

        // Link filter model with TreeView
        gtk_tree_view_set_model(listView, GTK_TREE_MODEL(filter_model));
    }

    // Apply the filter
    gtk_tree_model_filter_refilter(filter_model);
}

static gboolean filter_visible_func(GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
    GtkTreeModelFilter *filter_model = GTK_TREE_MODEL_FILTER(data);
    const gchar *search_text = g_object_get_data(G_OBJECT(filter_model), "search-text");
    gchar *service_name;
    gboolean visible = TRUE;

    // If search text is empty, show all rows
    if (search_text == NULL || search_text[0] == '\0')
    {
        return TRUE;
    }

    // Get the service name from column 2
    gtk_tree_model_get(model, iter, 1, &service_name, -1);

    // Check if the service name contains the search text
    if (service_name != NULL)
    {
        visible = (g_strstr_len(service_name, -1, search_text) != NULL);
        g_free(service_name);
    }

    return visible;
}

GtkWidget *createServicePage(GtkWidget *notebook, GtkWidget *window, gpointer user_data)
{
    modelCentral *data = (modelCentral *) user_data;

    GtkWidget *page;
    page = createPage(notebook, GTK_ORIENTATION_HORIZONTAL, 10, "Dịch vụ");

    GtkWidget *menuBoxForPageDichVu = createBox(page, GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(menuBoxForPageDichVu, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageDichVu, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc
    gtk_widget_set_size_request(menuBoxForPageDichVu, 300, -1);

    GtkWidget *searchBoxForPageDichVu = createBox(menuBoxForPageDichVu, GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *searchBarForPageDichVu = createSearch(searchBoxForPageDichVu);
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchBarForPageDichVu), "Tìm kiếm theo tên dịch vụ");
    gtk_widget_set_size_request(searchBarForPageDichVu, 300, -1);

    GtkWidget *buttonThemDichVu = createButton(menuBoxForPageDichVu, "Thêm dịch vụ");
    GtkWidget *buttonXoaDichVu = createButton(menuBoxForPageDichVu, "Xóa dịch vụ");
    GtkWidget *buttonSuaDichVu = createButton(menuBoxForPageDichVu, "Sửa dịch vụ");

    // Hiển thị danh sách khách hàng
    GtkWidget *listViewForPageDichVu = createTreeView(page);
    const gchar *columnNames[] = {"Mã DV", "Tên dịch vụ", "Giá"};
    createColumns(listViewForPageDichVu, columnNames, 3);
    
    // Tải dữ liệu file text vào Liststore khi khởi động chương trình
    load_file_txt_to_liststore(data->serviceList, "../database/services.txt");

    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageDichVu), GTK_TREE_MODEL(data->serviceList));

    // Handle search bar
    g_signal_connect(searchBarForPageDichVu, "search-changed", G_CALLBACK(onSearchChanged), listViewForPageDichVu);

    // Handle "Thêm dịch vụ" button
    ServiceData *service_data = g_new(ServiceData, 1);
    service_data->main_window = window;
    service_data->store = data->serviceList;
    service_data->customerList = data->customerList;
    service_data->billingList = data->billingList;
    g_signal_connect(buttonThemDichVu, "clicked", G_CALLBACK(addServices), service_data);

    // Handle "Xóa dịch vụ" button
    g_signal_connect(buttonXoaDichVu, "clicked", G_CALLBACK(deleteServices), service_data);

    // Handle "Sửa dịch vụ" button
    g_signal_connect(buttonSuaDichVu, "clicked", G_CALLBACK(editServices), service_data);

    // Giải phóng ServiceData khi dừng chương trình
    g_signal_connect(window, "destroy", G_CALLBACK(free_memory_when_main_window_destroy), service_data);

    return page;
}