#include "service.h"
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
    gchar *serviceId;
    gboolean visible = TRUE;

    // If search text is empty, show all rows
    if (search_text == NULL || strlen(search_text) == 0)
    {
        return TRUE;
    }

    // Get the serviceId from column 0
    gtk_tree_model_get(model, iter, 0, &serviceId, -1);

    // Check if the serviceId contains the search text
    if (serviceId != NULL)
    {
        visible = (g_strstr_len(serviceId, -1, search_text) != NULL);
        g_free(serviceId);
    }

    return visible;
}

GtkWidget *createServicePage(GtkWidget *notebook)
{
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
    GtkWidget *buttonSuaDichVu = createButton(menuBoxForPageDichVu, "Sửa dịch vụ");
    GtkWidget *buttonXoaDichVu = createButton(menuBoxForPageDichVu, "Xóa dịch vụ");

    // Hiển thị danh sách khách hàng
    GtkWidget *listViewForPageDichVu = createTreeView(page);
    const gchar *columnNames[] = {"Mã DV", "Tên dịch vụ", "Giá"};
    createColumns(listViewForPageDichVu, columnNames, 3);

    // Khởi tạo model cho danh sách khách hàng
    GtkListStore *serviceList = createListStore(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter;

    // Test data
    addData(serviceList, &iter, 0, "001", 1, "Sửa xe", 2, "100000", -1);
    addData(serviceList, &iter, 0, "002", 1, "Bảo dưỡng", 2, "200000", -1);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageDichVu), GTK_TREE_MODEL(serviceList));

    // Handle search bar
    g_signal_connect(searchBarForPageDichVu, "search-changed", G_CALLBACK(onSearchChanged), listViewForPageDichVu);
    return page;
}
