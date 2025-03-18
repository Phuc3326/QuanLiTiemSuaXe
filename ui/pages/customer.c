#include "customer.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../utils/listStore.h"

/**
 * Xử lý tìm kiếm trong danh sách khách hàng
 * @param entry Thanh tìm kiếm
 * @param user_data Dữ liệu người dùng (GtkListStore)
 */
static void on_search(GtkEntry *entry, gpointer user_data)
{
    GtkListStore *store = GTK_LIST_STORE(user_data);              // Kho dữ liệu
    GtkTreeModel *model = GTK_TREE_MODEL(store);                  // Model dữ liệu
    GtkTreeIter iter;                                             // Iterator
    const char *search_text = gtk_entry_get_text(entry);          // Lấy text tìm kiếm
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter); // Lấy iterator đầu tiên

    // Nếu không có text tìm kiếm, hiển thị tất cả
    if (strlen(search_text) == 0)
    {
        while (valid)
        {
            gtk_list_store_set(store, &iter, 5, TRUE, -1); // 5 là cột ẩn chứa trạng thái hiển thị
            valid = gtk_tree_model_iter_next(model, &iter);
        }
        return;
    }

    // Tìm kiếm theo biển số xe
    while (valid)
    {
        char *carPlate;
        gtk_tree_model_get(model, &iter, 3, &carPlate, -1); // 3 là cột biển số xe

        // Kiểm tra xem text tìm kiếm có xuất hiện trong biển số xe không
        gboolean found = (strstr(carPlate, search_text) != NULL);

        // Cập nhật trạng thái hiển thị
        gtk_list_store_set(store, &iter, 5, found, -1);

        // Giải phóng bộ nhớ
        g_free(carPlate);

        valid = gtk_tree_model_iter_next(model, &iter);
    }
}

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

    // Test data
    addData(customerList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "51G-12345", 4, "Honda Wave", -1);
    addData(customerList, &iter, 0, "KH001", 1, "Nguyễn Văn A", 2, "0123456789", 3, "51G-12345", 4, "test", -1);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageKhachHang), GTK_TREE_MODEL(customerList));

    // Handle search bar
    // TODO: Implement search bar
    return page;
}
