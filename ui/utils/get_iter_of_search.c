// tìm địa chỉ hàng trong Liststore của chuỗi người dùng tìm

#include <gtk/gtk.h>
#include "get_iter_of_search.h"
#include "../../modules/customers.h"

void display_customer_info(FindIterOfSearch *findData) 
{
    FindIterOfSearch *data = (FindIterOfSearch *) findData;
    GtkTreeModel *model = GTK_TREE_MODEL(data->list_store);
    GtkTreeIter *iter = data->result_iter;

    gchar *id_found, *name_found, *numberphone_found, *numberplate_found, *cartype_found;
    gtk_tree_model_get(model, iter, 0, &id_found, -1);
    gtk_tree_model_get(model, iter, 1, &name_found, -1);
    gtk_tree_model_get(model, iter, 2, &numberphone_found, -1);
    gtk_tree_model_get(model, iter, 3, &numberplate_found, -1);
    gtk_tree_model_get(model, iter, 4, &cartype_found, -1);

    GtkWidget *id = gtk_label_new(id_found);
    GtkWidget *name = gtk_label_new(name_found);
    GtkWidget *numberphone = gtk_label_new(numberphone_found);
    GtkWidget *numberplate = gtk_label_new(numberplate_found);
    GtkWidget *cartype = gtk_label_new(cartype_found);

    gtk_grid_attach(GTK_GRID(data->grid), id, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(data->grid), name, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(data->grid), numberphone, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(data->grid), numberplate, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(data->grid), cartype, 1, 4, 1, 1);

    gtk_widget_show_all(data->grid);
}

void search_in_liststore(GtkEntry *entry_search, gpointer findData)
{
    FindIterOfSearch *data = (FindIterOfSearch *) findData;
    const gchar *text_to_find = gtk_entry_get_text(entry_search);
    GtkTreeIter iter;

    GtkTreeModel *model = GTK_TREE_MODEL(data->list_store);

    if (gtk_tree_model_get_iter_first(model, &iter))
    {
        do 
        {
            gchar *cell_text;
            gtk_tree_model_get(model, &iter, data->search_column, &cell_text, -1);

            if (g_strcmp0(cell_text, text_to_find) == 0)
            {
                *data->result_iter = iter;  // lưu iter vào biến ngoài
                g_free(cell_text);
                display_customer_info(data);
                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}