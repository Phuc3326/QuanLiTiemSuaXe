// Giải phóng các con trỏ cần giữ đến khi dừng chương trình

#include <gtk/gtk.h>
#include "freeMemory.h"

void free_memory_when_main_window_destroy(GtkWidget *window, gpointer user_data)
{
    g_free(user_data);
}