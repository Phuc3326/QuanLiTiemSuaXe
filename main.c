#include <gtk/gtk.h>
#include "ui/index.c" // Ui Library

// Cấu hình cửa sổ
const char *WINDOW_TITLE = "Quản lí tiệm sửa xe";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

/**
 * Tạo notebook chính với tất cả các trang
 * @param window Cửa sổ chính
 */
// static void createNotebook(GtkWidget *window)
// {
//     GtkWidget *notebook;
//     GtkWidget *pageKhachHang, *pageDichVu, *pageThanhToan, *pageThongKe;
//     GtkWidget *labelKhachHang, *labelDichVu, *labelThanhToan, *labelThongKe;

//     // Tạo notebook
//     notebook = gtk_notebook_new();
//     gtk_widget_set_hexpand(notebook, TRUE); // Cho phép notebook mở rộng theo chiều ngang
//     gtk_widget_set_vexpand(notebook, TRUE); // Cho phép notebook mở rộng theo chiều dọc
//     gtk_container_add(GTK_CONTAINER(window), notebook);
//     gtk_widget_show(notebook);

//     // Tạo các trang
//     pageKhachHang = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Khách hàng");
//     pageDichVu = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Dịch vụ");
//     pageThanhToan = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Thanh toán");
//     pageThongKe = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Thống kê");

//     // [[ Trang Khách hàng ]]
//     GtkWidget *menuBoxForPageKhachHang = createMenuBox(pageKhachHang);
//     gtk_widget_set_halign(menuBoxForPageKhachHang, GTK_ALIGN_START); // Căn menu box về bên trái
//     gtk_widget_set_valign(menuBoxForPageKhachHang, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc

//     GtkWidget *listViewForPageKhachHang = createList(pageKhachHang);
//     gtk_widget_set_hexpand(listViewForPageKhachHang, TRUE); // Cho phép list view mở rộng theo chiều ngang
//     gtk_widget_set_vexpand(listViewForPageKhachHang, TRUE); // Cho phép list view mở rộng theo chiều dọc

//     GtkListStore *customerList = createListStore(); // Tạo kho dữ liệu

//     // Tạo model dữ liệu cho danh sách khách hàng
//     GtkTreeModel *filter_model = gtk_tree_model_filter_new(GTK_TREE_MODEL(customerList), NULL); // Tạo model filter
//     gtk_tree_model_filter_set_visible_column(GTK_TREE_MODEL_FILTER(filter_model), 5);           // Set cột ẩn chứa trạng thái hiển thị
//     gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageKhachHang), filter_model);             // Set model cho list view

//     // Tạo cột hiển thị
//     GtkTreeViewColumn *customerIdColumn = createViewColumn(listViewForPageKhachHang, "Mã KH", 0);
//     GtkTreeViewColumn *fullNameColumn = createViewColumn(listViewForPageKhachHang, "Họ tên", 1);
//     GtkTreeViewColumn *phoneNumberColumn = createViewColumn(listViewForPageKhachHang, "Số điện thoại", 2);
//     GtkTreeViewColumn *carPlateColumn = createViewColumn(listViewForPageKhachHang, "Biển số xe", 3);
//     GtkTreeViewColumn *carTypeColumn = createViewColumn(listViewForPageKhachHang, "Loại xe", 4);

//     // Tạo thanh tìm kiếm
//     GtkWidget *searchBoxForPageKhachHang = createMenuBox(menuBoxForPageKhachHang);
//     GtkWidget *searchBarForPageKhachHang = createSearch(searchBoxForPageKhachHang);
//     gtk_entry_set_placeholder_text(GTK_ENTRY(searchBarForPageKhachHang), "Tìm kiếm theo biển số xe");
//     gtk_widget_set_size_request(searchBarForPageKhachHang, 300, -1);

//     // Tạo những nút cần thiết
//     GtkWidget *buttonThemKhachHang = createButton(menuBoxForPageKhachHang, "Thêm khách hàng");
//     GtkWidget *buttonSuaKhachHang = createButton(menuBoxForPageKhachHang, "Sửa khách hàng");
//     GtkWidget *buttonXoaKhachHang = createButton(menuBoxForPageKhachHang, "Xóa khách hàng");

//     // Thêm dữ liệu mẫu
//     addData(customerList, "KH001", "Nguyễn Văn A", "0909090909", "51G-12345", "Toyota");
//     addData(customerList, "KH002", "Nguyễn Văn B", "0909090909", "51G-67890", "Honda");
//     addData(customerList, "KH003", "Nguyễn Văn C", "0909090909", "51G-11111", "Yamaha");

//     // Kết nối sự kiện tìm kiếm
//     g_signal_connect(searchBarForPageKhachHang, "changed", G_CALLBACK(on_search), customerList);

//     // Cập nhật filter model
//     gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(filter_model));

//     g_object_unref(customerList);
//     g_object_unref(filter_model);

//     // [[ Trang Dịch vụ ]]
// }

/**
 * Hàm xử lý khi ứng dụng được kích hoạt
 * @param app Thể hiện ứng dụng
 * @param user_data Dữ liệu người dùng
 */
static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = createWindow(app, WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
}

/**
 * Điểm vào chính của ứng dụng
 * @param argc Số lượng tham số
 * @param argv Mảng tham số
 * @return Trạng thái ứng dụng
 */
int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("quanlytiemsuaxe.gtk.development", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
