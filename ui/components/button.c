#include "button.h"

/**
 * Tạo button
 * @param parent Widget cha
 * @param label Nội dung nút
 * @return GtkWidget
 */
GtkWidget *createButton(GtkWidget *parent, const char *label)
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
