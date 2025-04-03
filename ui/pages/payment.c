#include "payment.h"
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

/**
 * Tạo trang thanh toán
 * @param notebook Notebook chứa trang thanh toán
 * @return Trang thanh toán
 */
GtkWidget *createPaymentPage(GtkWidget *notebook, GtkWidget *window)
{
    GtkWidget *page;
    page = createPage(notebook, GTK_ORIENTATION_HORIZONTAL, 10, "Thanh toán");

    GtkWidget *menuBoxForPageThanhToan = createBox(page, GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(menuBoxForPageThanhToan, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageThanhToan, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc
    gtk_widget_set_size_request(menuBoxForPageThanhToan, 300, -1);

    GtkWidget *buttonThemKhachHang = createButton(menuBoxForPageThanhToan, "Thêm khoản thanh toán");
    GtkWidget *buttonSuaKhachHang = createButton(menuBoxForPageThanhToan, "Sửa kkhoản thanh toán");
    GtkWidget *buttonXoaKhachHang = createButton(menuBoxForPageThanhToan, "Xóa khoản thanh toán");

    // Hiển thị danh sách khách hàng
    GtkWidget *listViewForPageThanhToan = createTreeView(page);
    const gchar *columnNames[] = {"Mã thanh toán", "Mã KH", "Ngày thanh toán", "Số tiền thanh toán", "Mã xe"};
    createColumns(listViewForPageThanhToan, columnNames, 5);

    // Khởi tạo model cho danh sách khách hàng
    GtkListStore *paymentList = createListStore(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter;

    // Test data
    addData(paymentList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "51G-12345", 4, "Honda Wave", -1);
    addData(paymentList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "52G-1", 4, "test", -1);

    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageThanhToan), GTK_TREE_MODEL(paymentList));

    // Handle search bar
    // g_signal_connect(searchBarForPageThanhToan, "changed", G_CALLBACK(onSearchChanged), listViewForPageThanhToan);

    return page;
}
