#ifndef FREE_MEMORY_H
#define FREE_MEMORY_H

#include <gtk/gtk.h>

void free_memory_when_main_window_destroy(GtkWidget *window, gpointer user_data);
void free_struct_and_iter_customer(GtkWidget *window, gpointer user_data);
void free_struct_and_iter_service(GtkWidget *window, gpointer user_data);

#endif