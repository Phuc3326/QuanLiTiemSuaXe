#ifndef SEARCH_IN_MODEL_H
#define SEARCH_IN_MODEL_H

#include <gtk/gtk.h>

void search_in_liststore_customer(GtkEntry *entry_search, gpointer findData);
void search_in_liststore_customer_edit(GtkEntry *entry_search, gpointer user_data);
void search_in_liststore_service(GtkEntry *entry_search, gpointer findData);
void search_in_liststore_service_edit(GtkEntry *entry_search, gpointer user_data);

#endif
