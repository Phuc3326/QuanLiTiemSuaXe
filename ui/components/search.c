#include "search.h"

/**
 * Tạo search bar
 * @param parent Widget cha
 * @return GtkWidget
 */
GtkWidget *createSearch(GtkWidget *parent)
{
    GtkWidget *search;
    search = gtk_search_entry_new();
    gtk_container_add(GTK_CONTAINER(parent), search);
    gtk_widget_show(search);
    return search;
}
