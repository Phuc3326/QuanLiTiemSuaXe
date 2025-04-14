#include <gtk/gtk.h>
#include "update_txt_bil.h"

void updateTXT_bil(GtkListStore *store, const char *filename)
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
        gchar *id, *time, *id_cus, *id_ser;
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                            0, &id,
                            1, &time,
                            2, &id_cus,
                            3, &id_ser,
                            -1);
        fprintf(file_pointer, "%s|%s|%s|%s\n", id, time, id_cus, id_ser);
                // Giải phóng bộ nhớ sau khi dùng
                g_free(id);
                g_free(time);
                g_free(id_cus);
                g_free(id_ser);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
        }

        // Đóng file
        fclose(file_pointer);
}