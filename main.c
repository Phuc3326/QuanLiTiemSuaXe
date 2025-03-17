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
static GtkWidget *createSearch(GtkWidget *parent)
{
    GtkWidget *input;
    input = gtk_search_entry_new();
    gtk_container_add(GTK_CONTAINER(parent), input);
    gtk_widget_show(input);
    return input;
}

/**
 * Tạo cột trong tree view
 * @param parent Widget cha
 * @param title Tiêu đề cột
 * @param column_index Chỉ số cột trong model
 * @return GtkTreeViewColumn
 */
static GtkTreeViewColumn *createViewColumn(GtkWidget *parent, const char *title, int column_index)
{
    GtkTreeViewColumn *viewColumn;
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    viewColumn = gtk_tree_view_column_new_with_attributes(title, renderer, "text", column_index, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(parent), viewColumn);
    return viewColumn;
}

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

/**
 * Tạo kho dữ liệu danh sách với 5 cột kiểu chuỗi và 1 cột boolean
 * @return GtkListStore
 */
static GtkListStore *createListStore()
{
    GtkListStore *store = gtk_list_store_new(6,
                                             G_TYPE_STRING, // Mã KH
                                             G_TYPE_STRING, // Họ tên
                                             G_TYPE_STRING, // Số điện thoại
                                             G_TYPE_STRING, // Biển số xe
                                             G_TYPE_STRING, // Loại xe
                                             G_TYPE_BOOLEAN // Trạng thái hiển thị
    );
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
    gtk_list_store_set(store, &iter,
                       0, customerId,
                       1, fullName,
                       2, phoneNumber,
                       3, carPlate,
                       4, carType,
                       5, TRUE, // Set trạng thái hiển thị mặc định là TRUE
                       -1);
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
    GtkWidget *menuBoxForPageKhachHang = createMenuBox(pageKhachHang);
    gtk_widget_set_halign(menuBoxForPageKhachHang, GTK_ALIGN_START); // Căn menu box về bên trái
    gtk_widget_set_valign(menuBoxForPageKhachHang, GTK_ALIGN_FILL);  // Cho phép menu box mở rộng theo chiều dọc

    GtkWidget *listViewForPageKhachHang = createList(pageKhachHang);
    gtk_widget_set_hexpand(listViewForPageKhachHang, TRUE); // Cho phép list view mở rộng theo chiều ngang
    gtk_widget_set_vexpand(listViewForPageKhachHang, TRUE); // Cho phép list view mở rộng theo chiều dọc

    GtkListStore *customerList = createListStore(); // Tạo kho dữ liệu

    // Tạo model dữ liệu cho danh sách khách hàng
    GtkTreeModel *filter_model = gtk_tree_model_filter_new(GTK_TREE_MODEL(customerList), NULL); // Tạo model filter
    gtk_tree_model_filter_set_visible_column(GTK_TREE_MODEL_FILTER(filter_model), 5);           // Set cột ẩn chứa trạng thái hiển thị
    gtk_tree_view_set_model(GTK_TREE_VIEW(listViewForPageKhachHang), filter_model);             // Set model cho list view

    // Tạo cột hiển thị
    GtkTreeViewColumn *customerIdColumn = createViewColumn(listViewForPageKhachHang, "Mã KH", 0);
    GtkTreeViewColumn *fullNameColumn = createViewColumn(listViewForPageKhachHang, "Họ tên", 1);
    GtkTreeViewColumn *phoneNumberColumn = createViewColumn(listViewForPageKhachHang, "Số điện thoại", 2);
    GtkTreeViewColumn *carPlateColumn = createViewColumn(listViewForPageKhachHang, "Biển số xe", 3);
    GtkTreeViewColumn *carTypeColumn = createViewColumn(listViewForPageKhachHang, "Loại xe", 4);

    // Tạo thanh tìm kiếm
    GtkWidget *searchBoxForPageKhachHang = createMenuBox(menuBoxForPageKhachHang);
    GtkWidget *searchBarForPageKhachHang = createSearch(searchBoxForPageKhachHang);
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchBarForPageKhachHang), "Tìm kiếm theo biển số xe");
    gtk_widget_set_size_request(searchBarForPageKhachHang, 300, -1);

    // Tạo những nút cần thiết
    GtkWidget *buttonThemKhachHang = createButton(menuBoxForPageKhachHang, "Thêm khách hàng");
    GtkWidget *buttonSuaKhachHang = createButton(menuBoxForPageKhachHang, "Sửa khách hàng");
    GtkWidget *buttonXoaKhachHang = createButton(menuBoxForPageKhachHang, "Xóa khách hàng");

    // Thêm dữ liệu mẫu
    addData(customerList, "KH001", "Nguyễn Văn A", "0909090909", "51G-12345", "Toyota");
    addData(customerList, "KH002", "Nguyễn Văn B", "0909090909", "51G-67890", "Honda");
    addData(customerList, "KH003", "Nguyễn Văn C", "0909090909", "51G-11111", "Yamaha");

    // Kết nối sự kiện tìm kiếm
    g_signal_connect(searchBarForPageKhachHang, "changed", G_CALLBACK(on_search), customerList);

    // Cập nhật filter model
    gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(filter_model));

    g_object_unref(customerList);
    g_object_unref(filter_model);

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
