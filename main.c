#include <gtk/gtk.h>

// Cấu hình cửa sổ
const char *WINDOW_TITLE = "Quản lí tiệm sửa xe";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

/**
 * Tạo nút bấm với khoảng cách chuẩn
 * @param parent Widget cha
 * @param label Nội dung nút
 * @return GtkWidget
 */
static GtkWidget *createButton(GtkWidget *parent, const char *label)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(label);
    gtk_widget_set_margin_start(button, 5);
    gtk_widget_set_margin_end(button, 5);
    gtk_widget_set_margin_top(button, 5);
    gtk_widget_set_margin_bottom(button, 5);
    gtk_container_add(GTK_CONTAINER(parent), button);
    gtk_widget_show(button);
    return button;
}

/**
 * Tạo trang mới trong notebook
 * @param notebook Widget notebook
 * @param orientation Hướng nội dung
 * @param spacing Khoảng cách giữa các phần tử
 * @param title Tiêu đề trang
 * @return GtkWidget
 */
static GtkWidget *
createPage(GtkNotebook *notebook, GtkOrientation orientation, int spacing, const char *title)
{
    GtkWidget *page;
    GtkWidget *label;
    page = gtk_box_new(orientation, spacing);
    label = gtk_label_new(title);
    gtk_widget_show(label);

    int pos = gtk_notebook_append_page(notebook, page, label);
    gtk_widget_show(page);

    GtkWidget *result = gtk_notebook_get_nth_page(notebook, pos);
    return result;
}

/**
 * Tạo khung menu dọc với khoảng cách chuẩn
 * @param parent Widget cha
 * @return GtkWidget
 */
static GtkWidget *createMenuBox(GtkWidget *parent)
{
    GtkWidget *menuBox;
    menuBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_margin_start(menuBox, 10);
    gtk_widget_set_margin_end(menuBox, 10);
    gtk_widget_set_margin_top(menuBox, 10);
    gtk_widget_set_margin_bottom(menuBox, 10);
    gtk_container_add(GTK_CONTAINER(parent), menuBox);
    gtk_widget_show(menuBox);
    return menuBox;
}

/**
 * Tạo danh sách có thể mở rộng
 * @param parent Widget cha
 * @return GtkWidget
 */
static GtkWidget *createList(GtkWidget *parent)
{
    GtkWidget *listView;
    listView = gtk_tree_view_new();
    gtk_widget_set_hexpand(listView, TRUE); // Cho phép mở rộng theo chiều ngang
    gtk_widget_set_vexpand(listView, TRUE); // Cho phép mở rộng theo chiều dọc
    gtk_container_add(GTK_CONTAINER(parent), listView);
    gtk_widget_show(listView);
    return listView;
}

/**
 * Tạo trường nhập liệu
 * @param parent Widget cha
 * @return GtkWidget
 */
static GtkWidget *createInput(GtkWidget *parent)
{
    GtkWidget *input;
    input = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(parent), input);
    gtk_widget_show(input);
    return input;
}

/**
 * Tạo cột trong tree view
 * @param parent Widget cha
 * @param title Tiêu đề cột
 * @return GtkTreeViewColumn
 */
static GtkTreeViewColumn *createViewColumn(GtkWidget *parent, const char *title)
{
    GtkTreeViewColumn *viewColumn;
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    viewColumn = gtk_tree_view_column_new_with_attributes(title, renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(parent), viewColumn);
    return viewColumn;
}

/**
 * Tạo kho dữ liệu danh sách với 5 cột kiểu chuỗi
 * @return GtkListStore
 */
static GtkListStore *createListStore()
{
    GtkListStore *store = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    return store;
}

/**
 * Thêm bản ghi khách hàng vào kho dữ liệu
 * @param store Kho dữ liệu
 * @param customerId Mã khách hàng
 * @param fullName Họ tên
 * @param phoneNumber Số điện thoại
 * @param carPlate Biển số xe
 * @param carType Loại xe
 */
static void addData(GtkListStore *store, const char *customerId, const char *fullName, const char *phoneNumber, const char *carPlate, const char *carType)
{
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, customerId, 1, fullName, 2, phoneNumber, 3, carPlate, 4, carType, -1);
}

/**
 * Tạo notebook chính với tất cả các trang
 * @param window Cửa sổ chính
 */
static void createNotebook(GtkWidget *window)
{
    GtkWidget *notebook;
    GtkWidget *pageKhachHang, *pageDichVu, *pageThanhToan, *pageThongKe;
    GtkWidget *labelKhachHang, *labelDichVu, *labelThanhToan, *labelThongKe;

    // Tạo notebook
    notebook = gtk_notebook_new();
    gtk_widget_set_hexpand(notebook, TRUE); // Cho phép notebook mở rộng theo chiều ngang
    gtk_widget_set_vexpand(notebook, TRUE); // Cho phép notebook mở rộng theo chiều dọc
    gtk_container_add(GTK_CONTAINER(window), notebook);
    gtk_widget_show(notebook);

    // Tạo các trang
    pageKhachHang = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Khách hàng");
    pageDichVu = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Dịch vụ");
    pageThanhToan = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Thanh toán");
    pageThongKe = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Thống kê");

    // [[ Trang Khách hàng ]]
    GtkWidget *menuBox = createMenuBox(pageKhachHang);
    gtk_widget_set_halign(menuBox, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBox, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc

    GtkWidget *buttonThemKhachHang = createButton(menuBox, "Thêm khách hàng");
    GtkWidget *buttonSuaKhachHang = createButton(menuBox, "Sửa khách hàng");
    GtkWidget *buttonXoaKhachHang = createButton(menuBox, "Xóa khách hàng");

    GtkWidget *listView = createList(pageKhachHang);
    gtk_widget_set_hexpand(listView, TRUE); // Cho phép list view mở rộng theo chiều ngang
    gtk_widget_set_vexpand(listView, TRUE); // Cho phép list view mở rộng theo chiều dọc

    GtkListStore *store = createListStore();

    // Tạo model dữ liệu cho danh sách khách hàng
    gtk_tree_view_set_model(GTK_TREE_VIEW(listView), GTK_TREE_MODEL(store));

    // Tạo cột hiển thị
    GtkTreeViewColumn *customerIdColumn = createViewColumn(listView, "Mã KH");
    GtkTreeViewColumn *fullNameColumn = createViewColumn(listView, "Họ tên");
    GtkTreeViewColumn *phoneNumberColumn = createViewColumn(listView, "Số điện thoại");
    GtkTreeViewColumn *carPlateColumn = createViewColumn(listView, "Biển số xe");
    GtkTreeViewColumn *carTypeColumn = createViewColumn(listView, "Loại xe");

    // Thêm dữ liệu mẫu
    // addData(store, "KH001", "Nguyễn Văn A", "0909090909", "1234567890", "Toyota");
    // addData(store, "KH002", "Nguyễn Văn B", "0909090909", "1234567890", "Toyota");
    // addData(store, "KH003", "Nguyễn Văn C", "0909090909", "1234567890", "Toyota");

    g_object_unref(store);
    // [[ Trang Dịch vụ ]]
}

/**
 * Khởi tạo các thành phần giao diện chính
 * @param window Cửa sổ chính
 */
static void createUI(GtkWidget *window)
{
    createNotebook(window);
}

/**
 * Hàm xử lý khi ứng dụng được kích hoạt
 * @param app Thể hiện ứng dụng
 * @param user_data Dữ liệu người dùng
 */
static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), WINDOW_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

    // Khởi tạo giao diện
    createUI(window);

    // Hiển thị cửa sổ và tất cả các widget con
    gtk_widget_show_all(window);
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

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
