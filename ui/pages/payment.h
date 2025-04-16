#ifndef PAYMENT_H
#define PAYMENT_H

#include <gtk/gtk.h>

GtkWidget *createPaymentPage(GtkWidget *notebook, GtkWidget *window, gpointer user_data);
void load_file_billing_txt_to_liststore(GtkListStore *store, const char *filename);

#endif
