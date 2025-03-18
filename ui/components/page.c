#include "page.h"

/**
 * Tạo trang mới trong notebook
 * @param notebook Widget notebook
 * @param orientation Hướng nội dung
 * @param spacing Khoảng cách giữa các phần tử
 * @param title Tiêu đề trang
 * @return GtkWidget
 */
GtkWidget *createPage(GtkWidget *notebook, GtkOrientation orientation, int spacing, const char *title)
{
    GtkWidget *page;
    GtkWidget *label;
    page = gtk_box_new(orientation, spacing);
    label = gtk_label_new(title);
    gtk_widget_show(label);

    int pos = gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, label);
    gtk_widget_show(page);

    GtkWidget *result = gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), pos);
    return result;
}