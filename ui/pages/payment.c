#include "payment.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"
#include "../utils/freeMemory.h"
#include "../../modules/billing.h"
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
        char id[10], time[20], id_cus[10], id_ser[10];
        
        // Lưu các chuỗi trong file (với đúng định dạng) vào các mảng đã khai báo
        // %9[^|]: lưu tối đa 9 ký tự hoặc dừng lại khi gặp |
        // %49[^\n]: lưu tối đa 49 ký tự hoặc dừng lại khi gặp \n
        if (sscanf(line, "%9[^|]|%19[^|]|%9[^|]|%9[^\n]", id, time, id_cus, id_ser) == 4) {
            GtkTreeIter iter;

            // Thêm hàng trong Liststore
            gtk_list_store_append(store, &iter);
            // Lưu vào Liststore
            gtk_list_store_set(store, &iter, 
                              0, id, 
                              1, time,
                              2, id_cus,
                              3, id_ser,
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
    gchar *billing_id;
    gboolean visible = TRUE;

    // If search text is empty, show all rows
    if (search_text == NULL || search_text[0] == '\0')
    {
        return TRUE;
    }

    // Get the billing id from column 1
    gtk_tree_model_get(model, iter, 0, &billing_id, -1);

    // Check if the plate number contains the search text
    if (billing_id != NULL)
    {
        visible = (g_strstr_len(billing_id, -1, search_text) != NULL);
        g_free(billing_id);
    }

    return visible;
}

GtkWidget *createPaymentPage(GtkWidget *notebook, GtkWidget *window, gpointer d)
{
    modelCentral *data = (modelCentral *) d;

    GtkWidget *page;
    page = createPage(notebook, GTK_ORIENTATION_HORIZONTAL, 10, "Hóa Đơn");

    GtkWidget *menuBoxForPageHoaDon = createBox(page, GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(menuBoxForPageHoaDon, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageHoaDon, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc
    gtk_widget_set_size_request(menuBoxForPageHoaDon, 300, -1);

    GtkWidget *searchBoxForPageHoaDon = createBox(menuBoxForPageHoaDon, GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *searchBarForPageHoaDon = createSearch(searchBoxForPageHoaDon);
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchBarForPageHoaDon), "Tìm kiếm theo mã khách hàng");
    gtk_widget_set_size_request(searchBarForPageHoaDon, 300, -1);

    GtkWidget *buttonTaoHoaDon = createButton(menuBoxForPageHoaDon, "Tạo hóa đơn");
    GtkWidget *buttonXuatHoaDon = createButton(menuBoxForPageHoaDon, "Xuất hóa đơn");

    // Hiển thị danh sách hóa đơn
    GtkWidget *listViewForPageHoaDon = createTreeView(page);
    const gchar *columnNames[] = {"Mã hóa đơn", "Thời gian", "Mã KH", "Mã DV", NULL};
    createColumns(listViewForPageHoaDon, columnNames, 4);
    
    // Tải dữ liệu file text vào Liststore khi khởi động chương trình
    load_file_txt_to_liststore(data->billingList, "../database/bills.txt");

    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageHoaDon), GTK_TREE_MODEL(data->billingList));

    // Handle search bar
    g_signal_connect(searchBarForPageHoaDon, "changed", G_CALLBACK(onSearchChanged), listViewForPageHoaDon);

    // Handle "Tạo hóa đơn" button
    BillData *user_data = g_new(BillData, 1);
    user_data->main_window = window;
    user_data->store = data->billingList;
    user_data->customerList = data->customerList;
    user_data->serviceList = data->serviceList;
    g_signal_connect(buttonTaoHoaDon, "clicked", G_CALLBACK(addBill), user_data);

    // Handle "Xuất hóa đơn" button
    g_signal_connect(buttonXuatHoaDon, "clicked", G_CALLBACK(exportBill), user_data);

    // Giải phóng BillData khi dừng chương trình
    g_signal_connect(window, "destroy", G_CALLBACK(free_memory_when_main_window_destroy), user_data);

    return page;
}
