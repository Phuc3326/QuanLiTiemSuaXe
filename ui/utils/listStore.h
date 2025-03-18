#ifndef LIST_STORE_H
#define LIST_STORE_H

#include <gtk/gtk.h>

GtkListStore *createListStore(int nColumns, ...);
void appendIter(GtkListStore *store, GtkTreeIter *iter);

#endif
