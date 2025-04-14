// tìm địa chỉ hàng trong Liststore của chuỗi người dùng tìm

#include <gtk/gtk.h>
#include "search_in_model.h"
#include "../../modules/customers.h"
#include "../../modules/services.h"

// Tab Customer
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

void search_in_liststore_customer(GtkEntry *entry_search, gpointer findData)
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

void display_customer_info_edit(FindIterOfSearch *findData,
    GtkEntry *id_entry,
    GtkEntry *name_entry,
    GtkEntry *numberphone_entry,
    GtkEntry *numberplate_entry,
    GtkEntry *cartype_entry) 
{
    GtkTreeModel *model = GTK_TREE_MODEL(findData->list_store);
    GtkTreeIter *iter = findData->result_iter;

    gchar *id_found, *name_found, *numberphone_found, *numberplate_found, *cartype_found;
    gtk_tree_model_get(model, iter,
    0, &id_found,
    1, &name_found,
    2, &numberphone_found,
    3, &numberplate_found,
    4, &cartype_found,
    -1);

    gtk_entry_set_text(id_entry, id_found);
    gtk_entry_set_text(name_entry, name_found);
    gtk_entry_set_text(numberphone_entry, numberphone_found);
    gtk_entry_set_text(numberplate_entry, numberplate_found);
    gtk_entry_set_text(cartype_entry, cartype_found);

    g_free(id_found);
    g_free(name_found);
    g_free(numberphone_found);
    g_free(numberplate_found);
    g_free(cartype_found);
}

void search_in_liststore_customer_edit(GtkEntry *entry_search, gpointer user_data)
{
    FindIterOfSearch *data = (FindIterOfSearch *) user_data;
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
                *data->result_iter = iter;
                g_free(cell_text);

                display_customer_info_edit(
                    data,
                    GTK_ENTRY(data->id_entry),
                    GTK_ENTRY(data->name_entry),
                    GTK_ENTRY(data->numberphone_entry),
                    GTK_ENTRY(data->numberplate_entry),
                    GTK_ENTRY(data->cartype_entry)
                );

                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}

// Tab Service

void display_service_info(FindIterOfSearch_service *findData) 
{
    FindIterOfSearch_service *data = (FindIterOfSearch_service *) findData;
    GtkTreeModel *model = GTK_TREE_MODEL(data->list_store);
    GtkTreeIter *iter = data->result_iter;

    gchar *id_found, *name_found, *cost_found;
    gtk_tree_model_get(model, iter, 0, &id_found, -1);
    gtk_tree_model_get(model, iter, 1, &name_found, -1);
    gtk_tree_model_get(model, iter, 2, &cost_found, -1);

    GtkWidget *id = gtk_label_new(id_found);
    GtkWidget *name = gtk_label_new(name_found);
    GtkWidget *cost = gtk_label_new(cost_found);

    gtk_grid_attach(GTK_GRID(data->grid), id, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(data->grid), name, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(data->grid), cost, 1, 2, 1, 1);

    gtk_widget_show_all(data->grid);
}

void search_in_liststore_service(GtkEntry *entry_search, gpointer findData)
{
    FindIterOfSearch_service *data = (FindIterOfSearch_service *) findData;
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
                display_service_info(data);
                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}

void display_service_info_edit(FindIterOfSearch_service *findData,
    GtkEntry *id_entry,
    GtkEntry *name_entry,
    GtkEntry *cost_entry) 
{
    GtkTreeModel *model = GTK_TREE_MODEL(findData->list_store);
    GtkTreeIter *iter = findData->result_iter;

    gchar *id_found, *name_found, *cost_found;
    gtk_tree_model_get(model, iter,
    0, &id_found,
    1, &name_found,
    2, &cost_found,
    -1);

    gtk_entry_set_text(id_entry, id_found);
    gtk_entry_set_text(name_entry, name_found);
    gtk_entry_set_text(cost_entry, cost_found);

    g_free(id_found);
    g_free(name_found);
    g_free(cost_found);
}

void search_in_liststore_service_edit(GtkEntry *entry_search, gpointer user_data)
{
    FindIterOfSearch_service *data = (FindIterOfSearch_service *) user_data;
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
                *data->result_iter = iter;
                g_free(cell_text);

                display_service_info_edit(
                    data,
                    GTK_ENTRY(data->id_entry),
                    GTK_ENTRY(data->name_entry),
                    GTK_ENTRY(data->cost_entry)
                );

                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}
