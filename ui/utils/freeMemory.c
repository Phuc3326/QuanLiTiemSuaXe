// Giải phóng các con trỏ cần giữ đến khi dừng chương trình

#include <gtk/gtk.h>
#include "freeMemory.h"
#include "../../modules/customers.h"
#include "../../modules/services.h"
#include "../../modules/billing.h"

void free_memory_when_main_window_destroy(GtkWidget *window, gpointer user_data)
{
    g_free(user_data);
}

void free_struct_and_iter_customer(GtkWidget *window, gpointer user_data)
{
    FindIterOfSearch *findData = (FindIterOfSearch *)user_data;
    if (findData) {
        if (findData->result_iter) {
            g_free(findData->result_iter);
        }
        g_free(findData);
    }
}

void free_struct_and_iter_service(GtkWidget *window, gpointer user_data)
{
    FindIterOfSearch_service *findData = (FindIterOfSearch_service *)user_data;
    if (findData) {
        if (findData->result_iter) {
            g_free(findData->result_iter);
        }
        g_free(findData);
    }
}

void free_struct_and_iter_billing(GtkWidget *window, gpointer user_data)
{
    FindIterOfSearch_billing *findData = (FindIterOfSearch_billing *)user_data;
    if (findData) {
        if (findData->result_iter) {
            g_free(findData->result_iter);
        }
        g_free(findData);
    }
}