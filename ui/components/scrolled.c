#include "scrolled.h"

/**
 * Tạo scrolled
 * @param parent Widget cha
 * @param child Widget muốn thêm thanh cuộn
 * @return GtkWidget
 */
GtkWidget *createScrolled(GtkWidget *parent, GtkWidget *child)
{
    GtkWidget *scrolled;
    scrolled = gtk_scrolled_window_new(NULL, NULL);
    // Thiết lập chính sách cuộn ngang/dọc
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                                    GTK_POLICY_NEVER,   // horizontal
                                                    GTK_POLICY_ALWAYS);  // vertical

    gtk_container_add(GTK_CONTAINER(scrolled), child);

    gtk_box_pack_start(GTK_BOX(parent), scrolled, TRUE, TRUE, 0);

    gtk_widget_show(scrolled);

    return scrolled;
}