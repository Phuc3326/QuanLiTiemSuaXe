#include <gtk/gtk.h>

const char *WINDOW_TITLE = "Quản lí tiệm sửa xe";
const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 768;

static void createNotebook(GtkWidget *window)
{
    GtkWidget *notebook;
    GtkWidget *page1, *page2, *page3, *page4;
    GtkWidget *label1, *label2, *label3, *label4;

    // Create notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // Tạo các trang
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Tạo các tab
    label1 = gtk_label_new("Khách hàng");
    label2 = gtk_label_new("Dịch vụ");
    label3 = gtk_label_new("Thanh toán");
    label4 = gtk_label_new("Thống kê");

    // Thêm các trang trang tương ứng vào notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, label1);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, label2);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, label3);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, label4);
}

static void createUI(GtkWidget *window)
{
    createNotebook(window);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), WINDOW_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_present(GTK_WINDOW(window));

    // Khởi tạo giao diện
    createUI(window);
}

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
