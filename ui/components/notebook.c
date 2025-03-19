#include "notebook.h"

/**
 * Tạo notebook
 * @param window Cửa sổ chính
 * @return Notebook
 */
GtkWidget *createNotebook(GtkWidget *window)
{
    GtkWidget *notebook;
    notebook = gtk_notebook_new();
    gtk_widget_set_hexpand(notebook, TRUE); // Cho phép notebook mở rộng theo chiều ngang
    gtk_widget_set_vexpand(notebook, TRUE); // Cho phép notebook mở rộng theo chiều dọc
    gtk_container_add(GTK_CONTAINER(window), notebook);
    gtk_widget_show(notebook);

    return notebook;
}