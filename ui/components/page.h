#ifndef PAGE_H
#define PAGE_H

#include <gtk/gtk.h>

GtkWidget *createPage(GtkWidget *notebook, GtkOrientation orientation, int spacing, const char *title);

#endif
