#ifndef SERVICES_H
#define SERVICES_H

#include <gtk/gtk.h>

// Struct để truyền vào hàm addCustomers
typedef struct 
{
    GtkWidget *main_window;
    GtkListStore *store;
} ServiceData;

// Struct để truyền vào hàm on_save_clicked
typedef struct {
    GtkWidget *id_entry;
    GtkWidget *name_entry;
    GtkWidget *cost_entry;
    GtkListStore *store;
} AddServiceData;

void addServices(GtkWidget *widget, gpointer user_data);
static void addData(GtkListStore *store, const char *filename, ...);
void deleteServices(GtkWidget *widget, gpointer user_data);
void editServices(GtkWidget *widget, gpointer user_data);

#endif
