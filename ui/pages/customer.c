#include "customer.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"

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
        // Get the child model
        model = gtk_tree_model_filter_get_model(GTK_TREE_MODEL_FILTER(model));
    }

    search_text = gtk_entry_get_text(GTK_ENTRY(searchBar));

    // Create filter model
    filter_model = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(model, NULL));

    // Store search text as object data to use in filter function
    g_object_set_data_full(G_OBJECT(filter_model), "search-text",
                           g_strdup(search_text), (GDestroyNotify)g_free);

    // Set visible function
    gtk_tree_model_filter_set_visible_func(filter_model,
                                           (GtkTreeModelFilterVisibleFunc)filter_visible_func, filter_model, NULL);

    // Apply the filter
    gtk_tree_model_filter_refilter(filter_model);

    // Set the filtered model to the tree view
    gtk_tree_view_set_model(listView, GTK_TREE_MODEL(filter_model));

    // Release our reference as the tree view will hold its own
    g_object_unref(filter_model);
}

static gboolean filter_visible_func(GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
    GtkTreeModelFilter *filter_model = GTK_TREE_MODEL_FILTER(data);
    const gchar *search_text = g_object_get_data(G_OBJECT(filter_model), "search-text");
    gchar *plate_number;
    gboolean visible = TRUE;

    // If search text is empty, show all rows
    if (search_text == NULL || strlen(search_text) == 0)
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

GtkWidget *createCustomerPage(GtkWidget *notebook)
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
    GtkTreeViewColumn *customerIdColumn = createTreeViewColumn(listViewForPageKhachHang, "Mã KH", 0);
    GtkTreeViewColumn *fullNameColumn = createTreeViewColumn(listViewForPageKhachHang, "Họ tên", 1);
    GtkTreeViewColumn *phoneNumberColumn = createTreeViewColumn(listViewForPageKhachHang, "Số điện thoại", 2);
    GtkTreeViewColumn *carPlateColumn = createTreeViewColumn(listViewForPageKhachHang, "Biển số xe", 3);
    GtkTreeViewColumn *carTypeColumn = createTreeViewColumn(listViewForPageKhachHang, "Loại xe", 4);

    // Khởi tạo model cho danh sách khách hàng
    GtkListStore *customerList = createListStore(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter;

    // Test data
    addData(customerList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "51G-12345", 4, "Honda Wave", -1);
    addData(customerList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "52G-1", 4, "test", -1);

    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageKhachHang), GTK_TREE_MODEL(customerList));

    // Handle search bar
    g_signal_connect(searchBarForPageKhachHang, "changed", G_CALLBACK(onSearchChanged), listViewForPageKhachHang);

    return page;
}
