#ifndef BILLING_H
#define BILLING_H

#include <gtk/gtk.h>

// Struct để truyền vào hàm addBill
typedef struct 
{
    GtkWidget *main_window;
    GtkListStore *store;
    GtkListStore *customerList;
    GtkListStore *serviceList;
} BillData;

// Struct để truyền vào hàm on_create_clicked
typedef struct {
    GtkWidget *id_entry;
    GtkWidget *time_entry;
    GtkWidget *id_cus_entry;
    GtkWidget *id_ser_entry;
    GtkListStore *store;
} AddBillData;

typedef struct 
{
    GtkListStore *list_store;
    gint search_column;
    GtkTreeIter *result_iter;
    GtkWidget *grid;
    GtkWidget *grid_pay;
    // Các label cần cho việc hiện thông tin trong các cửa sổ con
    GtkWidget *id_label;       
    GtkWidget *name_label;
    GtkWidget *numberphone_label;
    GtkWidget *numberplate_label;
    GtkWidget *cartype_label;
    GtkWidget *id_bil_label;
    GtkWidget *id_ser_label;
    GtkWidget *ser_name_label;
    GtkWidget *cost_label;
    GtkWidget *time_label; 
    // Liststore
    GtkListStore *customerList;
    GtkListStore *serviceList;
} FindIterOfSearch_billing;

void addBill(GtkWidget *widget, gpointer user_data);
static void addData(GtkListStore *store, const char *filename, ...);
void exportBill(GtkWidget *widget, gpointer user_data);

#endif
