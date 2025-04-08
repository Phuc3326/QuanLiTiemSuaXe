#include "customer.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"
#include "../utils/freeMemory.h"
#include "../../modules/customers.h"

// Hàm tải nội dung từ file text vào Liststore
void load_file_to_list_store(GtkListStore *store, const char *filename) {
    
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
        char id[10], name[100], phone[20], plate[20], type[50];
        
        // Lưu các chuỗi trong file (với đúng định dạng) vào các mảng đã khai báo
        // %9[^|]: lưu tối đa 9 ký tự hoặc dừng lại khi gặp |
        // %49[^\n]: lưu tối đa 49 ký tự hoặc dừng lại khi gặp \n
        if (sscanf(line, "%9[^|]|%99[^|]|%19[^|]|%19[^|]|%49[^\n]", id, name, phone, plate, type) == 5) {
            GtkTreeIter iter;

            // Thêm hàng trong Liststore
            gtk_list_store_append(store, &iter);
            // Lưu vào Liststore
            gtk_list_store_set(store, &iter, 
                              0, id, 
                              1, name, 
                              2, phone, 
                              3, plate,
                              4, type,
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
    gchar *plate_number;
    gboolean visible = TRUE;

    // If search text is empty, show all rows
    if (search_text == NULL || search_text[0] == '\0')
    {
        return TRUE;
    }

    // Get the plate number from column 3
    gtk_tree_model_get(model, iter, 3, &plate_number, -1);

    // Check if the plate number contains the search text
    if (plate_number != NULL)
    {
        visible = (g_strstr_len(plate_number, -1, search_text) != NULL);
        g_free(plate_number);
    }

    return visible;
}

GtkWidget *createCustomerPage(GtkWidget *notebook, GtkWidget *window)
{
    GtkWidget *page;
    page = createPage(notebook, GTK_ORIENTATION_HORIZONTAL, 10, "Khách hàng");

    GtkWidget *menuBoxForPageKhachHang = createBox(page, GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(menuBoxForPageKhachHang, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageKhachHang, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc
    gtk_widget_set_size_request(menuBoxForPageKhachHang, 300, -1);

    GtkWidget *searchBoxForPageKhachHang = createBox(menuBoxForPageKhachHang, GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *searchBarForPageKhachHang = createSearch(searchBoxForPageKhachHang);
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchBarForPageKhachHang), "Tìm kiếm theo biển số xe");
    gtk_widget_set_size_request(searchBarForPageKhachHang, 300, -1);

    GtkWidget *buttonThemKhachHang = createButton(menuBoxForPageKhachHang, "Thêm khách hàng");
    GtkWidget *buttonSuaKhachHang = createButton(menuBoxForPageKhachHang, "Sửa khách hàng");
    GtkWidget *buttonXoaKhachHang = createButton(menuBoxForPageKhachHang, "Xóa khách hàng");

    // Hiển thị danh sách khách hàng
    GtkWidget *listViewForPageKhachHang = createTreeView(page);
    const gchar *columnNames[] = {"Mã KH", "Tên KH", "SĐT", "Biển số", "Loại xe", NULL};
    createColumns(listViewForPageKhachHang, columnNames, 5);

    // Khởi tạo model cho danh sách khách hàng
    GtkListStore *customerList = createListStore(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    
    // Tải dữ liệu file text vào Liststore khi khởi động chương trình
    load_file_to_list_store(customerList, "../database/customers.txt");

    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageKhachHang), GTK_TREE_MODEL(customerList));

    // Handle search bar
    g_signal_connect(searchBarForPageKhachHang, "changed", G_CALLBACK(onSearchChanged), listViewForPageKhachHang);

    // Handle "Thêm khách hàng" button
    CustomerData *user_data = g_new(CustomerData, 1);
    user_data->main_window = window;
    user_data->store = customerList;
    g_signal_connect(buttonThemKhachHang, "clicked", G_CALLBACK(addCustomers), user_data);

    // Giải phóng user_data khi dừng chương trình
    g_signal_connect(window, "destroy", G_CALLBACK(free_memory_when_main_window_destroy), user_data);

    return page;
}
