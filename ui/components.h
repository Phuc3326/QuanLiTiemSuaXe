#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <gtk/gtk.h>

GtkWidget *createNotebook(GtkWidget *window);
GtkWidget *createPage(GtkWidget *notebook, GtkOrientation orientation, int spacing, const char *title);
#endif
