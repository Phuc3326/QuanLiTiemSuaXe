#include <gtk/gtk.h>

/**
 * Tạo grid
 * @param parent Widget cha
 * @return GtkWidget
 */
GtkWidget *createGrid(GtkWidget *parent)
{
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(parent), grid);
    gtk_widget_show(grid);
    return grid;
}