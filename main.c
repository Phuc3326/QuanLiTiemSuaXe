#include <gtk/gtk.h>
#include "ui/ui.h" // Ui Library

// Cấu hình cửa sổ
const char *WINDOW_TITLE = "Quản lí tiệm sửa xe";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

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
