#include <gtk/gtk.h>

// Tiêu đề của cửa sổ
const char *WINDOW_TITLE = "Quản lí tiệm sửa xe";

// Chiều rộng của cửa sổ
const int WINDOW_WIDTH = 1366;

// Chiều cao của cửa sổ
const int WINDOW_HEIGHT = 768;

/**
 * @author Jacky
 * @details Tạo button
 * @param parent Cha
 * @param label Nội dung của button
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
 *
 * @author Jacky
 * @details Tạo trang mới cho notebook
 * @param notebook Notebook
 * @param orientation Hướng của các nội dung trong trang
 * @param spacing Khoảng cách giữa các phần tử
 * @param title Tiêu đề của trang
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
 * @author Jacky
 * @details Tạo menu box
 * @param parent Cha
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

static GtkWidget *createList(GtkWidget *parent)
{
    GtkWidget *listView;
    listView = gtk_tree_view_new();
    gtk_container_add(GTK_CONTAINER(parent), listView);
    gtk_widget_show(listView);
    return listView;
}

/**
 *
 * @author Jacky
 * @details Tạo notebook
 * @param window Cửa sổ
 * @return void
 */
static void createNotebook(GtkWidget *window)
{
    GtkWidget *notebook;
    GtkWidget *pageKhachHang, *pageDichVu, *pageThanhToan, *pageThongKe;
    GtkWidget *labelKhachHang, *labelDichVu, *labelThanhToan, *labelThongKe;

    // Create notebook
    notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);
    gtk_widget_show(notebook);

    // Tạo các trang
    pageKhachHang = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Khách hàng");
    pageDichVu = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Dịch vụ");
    pageThanhToan = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Thanh toán");
    pageThongKe = createPage(GTK_NOTEBOOK(notebook), GTK_ORIENTATION_HORIZONTAL, 5, "Thống kê");

    // [[ Page Khách hàng ]]
    GtkWidget *menuBox = createMenuBox(pageKhachHang);
    GtkWidget *buttonThemKhachHang = createButton(menuBox, "Thêm khách hàng");
    GtkWidget *buttonSuaKhachHang = createButton(menuBox, "Sửa khách hàng");
    GtkWidget *buttonXoaKhachHang = createButton(menuBox, "Xóa khách hàng");

    GtkWidget *listView = createList(pageKhachHang);
    // [[ Page Dịch vụ ]]
}

/**
 *
 * @author Jacky
 * @details Tạo giao diện
 * @param window Cửa sổ
 * @return void
 */
static void createUI(GtkWidget *window)
{
    // Toàn bộ các component sẽ được khởi tạo ở đây
    createNotebook(window);
}

/**
 *
 * @author Jacky
 * @details Kích hoạt ứng dụng
 * @param app Ứng dụng
 * @param user_data Dữ liệu người dùng
 * @return void
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
 *
 * @author Jacky
 * @details Chính
 * @param argc Số lượng tham số
 * @param argv Tham số
 * @return int
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
