#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <gtk/gtk.h>

GtkWidget *createCustomerPage(GtkWidget *notebook, GtkWidget *window, gpointer user_data);
void load_file_customer_txt_to_liststore(GtkListStore *store, const char *filename);

#endif