#ifndef INDEX_H
#define INDEX_H

#include <gtk/gtk.h>

GtkWidget *createWindow(GtkApplication *app, const char *title, int width, int height);
void createUI(GtkWidget *window);

#endif
