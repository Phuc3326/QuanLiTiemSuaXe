#include "customer.h"
#include "../components/box.c"
#include "../components/button.c"
#include "../components/treeView.c"
#include "../components/search.c"
#include "../utils/listStore.c"

GtkWidget *createCustomerPage(GtkWidget *notebook)
{
    GtkWidget *page;
    page = createPage(notebook, GTK_ORIENTATION_HORIZONTAL, 10, "Khách hàng");

    GtkWidget *menuBoxForPageKhachHang = createBox(page, GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(menuBoxForPageKhachHang, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageKhachHang, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc

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
    addData(customerList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "51G-12345", 4, "Honda Wave", -1);
    addData(customerList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "51G-12345", 4, "test", -1);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageKhachHang), GTK_TREE_MODEL(customerList));
    g_object_unref(customerList);

    // Handle search bar
    g_signal_connect(searchBarForPageKhachHang, "search-changed", G_CALLBACK(on_search), customerList);
    return page;
}
