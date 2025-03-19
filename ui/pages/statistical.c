#include "statistical.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"

/**
 * Tạo trang thống kê
 * @param notebook Notebook chứa trang thống kê
 * @return Trang thống kê
 */
GtkWidget *createStatisticalPage(GtkWidget *notebook)
{
    GtkWidget *page;
    page = createPage(notebook, GTK_ORIENTATION_HORIZONTAL, 10, "Thống kê");

    GtkWidget *menuBoxForPageThongKe = createBox(page, GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(menuBoxForPageThongKe, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageThongKe, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc
    gtk_widget_set_size_request(menuBoxForPageThongKe, 300, -1);

    GtkWidget *searchBoxForPageDichVu = createBox(menuBoxForPageThongKe, GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *searchBarForPageDichVu = createSearch(searchBoxForPageDichVu);
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchBarForPageDichVu), "Tìm kiếm theo tên dịch vụ");
    gtk_widget_set_size_request(searchBarForPageDichVu, 300, -1);

    GtkWidget *buttonThemDichVu = createButton(menuBoxForPageThongKe, "Thêm dịch vụ");
    GtkWidget *buttonSuaDichVu = createButton(menuBoxForPageThongKe, "Sửa dịch vụ");
    GtkWidget *buttonXoaDichVu = createButton(menuBoxForPageThongKe, "Xóa dịch vụ");

    // Hiển thị danh sách khách hàng
    GtkWidget *listViewForPageThongKe = createTreeView(page);
    GtkTreeViewColumn *serviceIdColumn = createTreeViewColumn(listViewForPageThongKe, "Mã DV", 0);
    GtkTreeViewColumn *serviceNameColumn = createTreeViewColumn(listViewForPageThongKe, "Tên dịch vụ", 1);
    GtkTreeViewColumn *servicePriceColumn = createTreeViewColumn(listViewForPageThongKe, "Giá", 2);

    // Khởi tạo model cho danh sách khách hàng
    GtkListStore *serviceList = createListStore(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter;

    // Test data
    addData(serviceList, &iter, 0, "001", 1, "Sửa xe", 2, "100000", -1);
    addData(serviceList, &iter, 0, "002", 1, "Bảo dưỡng", 2, "200000", -1);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageThongKe), GTK_TREE_MODEL(serviceList));

    // Handle search bar
    // g_signal_connect(searchBarForPageThongKe, "search-changed", G_CALLBACK(onSearchChanged), listViewForPageThongKe);
    return page;
}
