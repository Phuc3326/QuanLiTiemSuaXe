#include "treeView.h"

/**
 * Tạo cột trong tree view
 * @param parent Widget cha
 * @param title Tiêu đề cột
 * @param column_index Chỉ số cột trong model
 * @return GtkTreeViewColumn
 */
GtkTreeViewColumn *createTreeViewColumn(GtkWidget *parent, const char *title, int column_index)
{
    GtkTreeViewColumn *viewColumn;
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    viewColumn = gtk_tree_view_column_new_with_attributes(title, renderer, "text", column_index, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(parent), viewColumn);
    gtk_tree_view_column_set_visible(viewColumn, TRUE);
    return viewColumn;
}

/**
 * Tạo tree view
 * @param parent Widget cha
 * @return GtkTreeView
 */
GtkWidget *createTreeView(GtkWidget *parent)
{
    GtkWidget *treeView;
    treeView = gtk_tree_view_new();
    gtk_widget_set_hexpand(treeView, TRUE); // Cho phép mở rộng theo chiều ngang
    gtk_widget_set_vexpand(treeView, TRUE); // Cho phép mở rộng theo chiều dọc
    gtk_container_add(GTK_CONTAINER(parent), treeView);
    gtk_widget_show(treeView);
    return treeView;
}