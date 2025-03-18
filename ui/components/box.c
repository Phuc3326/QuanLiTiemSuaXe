#include "box.h"

/**
 * Tạo box
 * @param parent Widget cha
 * @param orientation Hướng nội dung
 * @param spacing Khoảng cách giữa các phần tử
 * @return GtkWidget
 */
GtkWidget *createBox(GtkWidget *parent, GtkOrientation orientation, int spacing)
{
    GtkWidget *box;
    box = gtk_box_new(orientation, spacing);
    gtk_widget_set_margin_start(box, 10);
    gtk_widget_set_margin_end(box, 10);
    gtk_widget_set_margin_top(box, 10);
    gtk_widget_set_margin_bottom(box, 10);
    gtk_container_add(GTK_CONTAINER(parent), box);
    gtk_widget_show(box);
    return box;
}
