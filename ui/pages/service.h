#ifndef SERVICE_H
#define SERVICE_H

#include <gtk/gtk.h>

GtkWidget *createServicePage(GtkWidget *notebook, GtkWidget *window, gpointer user_data);
void load_file_service_txt_to_liststore(GtkListStore *store, const char *filename);

#endif
