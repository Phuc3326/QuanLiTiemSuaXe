#include <gtk/gtk.h>
#include "update_txt_ser.h"

void updateTXT_ser(GtkListStore *store, const char *filename)
{
        GtkTreeIter iter;

        // Mở file
        FILE *file_pointer = fopen(filename, "w");

        // Nếu không mở được file thì thoát
        if (!file_pointer) return;
    
        // Lấy con trỏ đến hàng đầu tiên trong Listore
        gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);
    
        // Lấy dữ liệu từ liststore rồi ghi file
        while (valid)
        {
        gchar *id, *name, *cost;
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                            0, &id,
                            1, &name,
                            2, &cost,
                            -1);
        fprintf(file_pointer, "%s|%s|%s\n", id, name, cost);
                // Giải phóng bộ nhớ sau khi dùng
                g_free(id);
                g_free(name);
                g_free(cost);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
        }

        // Đóng file
        fclose(file_pointer);
}