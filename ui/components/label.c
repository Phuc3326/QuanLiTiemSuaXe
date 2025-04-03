#include <gtk/gtk.h>

/**
 * Tạo label
 * @param parent Widget cha
 * @param char Nội dung label
 * @return GtkWidget
 */
GtkWidget *createLabel(GtkWidget *parent, const gchar *text)
{
    GtkWidget *label = gtk_label_new(text);
    gtk_widget_set_margin_start(label, 5);
    gtk_widget_set_margin_end(label, 5);
    gtk_widget_set_margin_top(label, 5);
    gtk_widget_set_margin_bottom(label, 5);
    gtk_container_add(GTK_CONTAINER(parent), label);
    gtk_widget_show(label);
    return label;
}