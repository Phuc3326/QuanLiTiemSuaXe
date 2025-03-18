#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <gtk/gtk.h>

GtkTreeViewColumn *createTreeViewColumn(GtkWidget *parent, const char *title, int column_index);
GtkWidget *createTreeView(GtkWidget *parent);

#endif
