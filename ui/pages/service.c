#include "service.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"

GtkWidget *createServicePage(GtkWidget *notebook)
{
    GtkWidget *page;
    page = createPage(notebook, GTK_ORIENTATION_HORIZONTAL, 10, "Dịch vụ");

    GtkWidget *menuBoxForPageDichVu = createBox(page, GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(menuBoxForPageDichVu, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageDichVu, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc

    // GtkWidget *searchBoxForPageDichVu = createBox(menuBoxForPageDichVu, GTK_ORIENTATION_HORIZONTAL, 10);
    // GtkWidget *searchBarForPageDichVu = createSearch(searchBoxForPageDichVu);
    // gtk_entry_set_placeholder_text(GTK_ENTRY(searchBarForPageDichVu), "Tìm kiếm theo tên dịch vụ");
    // gtk_widget_set_size_request(searchBarForPageKhachHang, 300, -1);

    GtkWidget *buttonThemDichVu = createButton(menuBoxForPageDichVu, "Thêm dịch vụ");
    GtkWidget *buttonSuaDichVu = createButton(menuBoxForPageDichVu, "Sửa dịch vụ");
    GtkWidget *buttonXoaDichVu = createButton(menuBoxForPageDichVu, "Xóa dịch vụ");

    // Hiển thị danh sách khách hàng
    GtkWidget *listViewForPageDichVu = createTreeView(page);
    GtkTreeViewColumn *serviceIdColumn = createTreeViewColumn(listViewForPageDichVu, "Mã DV", 0);
    GtkTreeViewColumn *serviceNameColumn = createTreeViewColumn(listViewForPageDichVu, "Tên dịch vụ", 1);
    GtkTreeViewColumn *servicePriceColumn = createTreeViewColumn(listViewForPageDichVu, "Giá", 2);

    // Khởi tạo model cho danh sách khách hàng
    GtkListStore *serviceList = createListStore(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter;

    // Test data
    addData(serviceList, &iter, 0, "DV001", 1, "Sửa xe", 2, "100000", -1);
    addData(serviceList, &iter, 0, "DV002", 1, "Bảo dưỡng", 2, "200000", -1);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageDichVu), GTK_TREE_MODEL(serviceList));

    // Handle search bar
    // TODO: Implement search bar
    return page;
}
