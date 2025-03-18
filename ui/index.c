#include <gtk/gtk.h>
#include "index.h"
#include "components.c"
#include "pages/customer.c"

/**
 * Tạo giao diện chính
 * @param window Cửa sổ chính
 */
void createUI(GtkWidget *window)
{
    GtkWidget *notebook = createNotebook(window);
    createCustomerPage(notebook);
}

/**
 * Tạo cửa sổ chính
 * @param app Thể hiện ứng dụng
 * @param title Tiêu đề cửa sổ
 * @param width Chiều rộng cửa sổ
 * @param height Chiều cao cửa sổ
 * @return Cửa sổ chính
 */
GtkWidget *createWindow(GtkApplication *app, const char *title, int width, int height)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    // Khởi tạo giao diện
    createUI(window);

    // Hiển thị cửa sổ và tất cả các widget con
    gtk_widget_show_all(window);

    return window;
}
