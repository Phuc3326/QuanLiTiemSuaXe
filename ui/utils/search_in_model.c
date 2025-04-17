// tìm địa chỉ hàng trong Liststore của chuỗi người dùng tìm

#include <gtk/gtk.h>
#include "search_in_model.h"
#include "../../modules/customers.h"
#include "../../modules/services.h"
#include "../../modules/billing.h"

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

    // Nếu các label chưa được tạo, tạo mới và gắn vào grid
    if (!data->id_label) {
        data->id_label = gtk_label_new(id_found);
        data->name_label = gtk_label_new(name_found);
        data->numberphone_label = gtk_label_new(numberphone_found);
        data->numberplate_label = gtk_label_new(numberplate_found);
        data->cartype_label = gtk_label_new(cartype_found);

        gtk_grid_attach(GTK_GRID(data->grid), data->id_label, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->name_label, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->numberphone_label, 1, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->numberplate_label, 1, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->cartype_label, 1, 4, 1, 1);
    } else {
        // Cập nhật nội dung của các label
        gtk_label_set_text(GTK_LABEL(data->id_label), id_found);
        gtk_label_set_text(GTK_LABEL(data->name_label), name_found);
        gtk_label_set_text(GTK_LABEL(data->numberphone_label), numberphone_found);
        gtk_label_set_text(GTK_LABEL(data->numberplate_label), numberplate_found);
        gtk_label_set_text(GTK_LABEL(data->cartype_label), cartype_found);
    }

    // Giải phóng bộ nhớ
    g_free(id_found);
    g_free(name_found);
    g_free(numberphone_found);
    g_free(numberplate_found);
    g_free(cartype_found);

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
    // GtkEntry *id_entry,
    GtkEntry *name_entry,
    GtkEntry *numberphone_entry,
    GtkEntry *numberplate_entry,
    GtkEntry *cartype_entry) 
{
    FindIterOfSearch *data = (FindIterOfSearch *) findData;
    GtkTreeModel *model = GTK_TREE_MODEL(data->list_store);
    GtkTreeIter *iter = data->result_iter;

    gchar *name_found, *numberphone_found, *numberplate_found, *cartype_found;
    gtk_tree_model_get(model, iter,
    // 0, &id_found,
    1, &name_found,
    2, &numberphone_found,
    3, &numberplate_found,
    4, &cartype_found,
    -1);

    // gtk_entry_set_text(id_entry, id_found);
    gtk_entry_set_text(name_entry, name_found);
    gtk_entry_set_text(numberphone_entry, numberphone_found);
    gtk_entry_set_text(numberplate_entry, numberplate_found);
    gtk_entry_set_text(cartype_entry, cartype_found);

    // g_free(id_found);
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
                    // GTK_ENTRY(data->id_entry),
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

    // Cập nhật hoặc tạo mới các nhãn
    if (!data->id_label) {
        data->id_label = gtk_label_new(id_found);
        data->name_label = gtk_label_new(name_found);
        data->cost_label = gtk_label_new(cost_found);

        gtk_grid_attach(GTK_GRID(data->grid), data->id_label, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->name_label, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->cost_label, 1, 2, 1, 1);
    } else {
        gtk_label_set_text(GTK_LABEL(data->id_label), id_found);
        gtk_label_set_text(GTK_LABEL(data->name_label), name_found);
        gtk_label_set_text(GTK_LABEL(data->cost_label), cost_found);
    }

    g_free(id_found);
    g_free(name_found);
    g_free(cost_found);

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
    FindIterOfSearch_service *data = (FindIterOfSearch_service *) findData;
    GtkTreeModel *model = GTK_TREE_MODEL(data->list_store);
    GtkTreeIter *iter = data->result_iter;

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

// Tab billing

void display_customer_info_for_payment(FindIterOfSearch_billing *findData) 
{
    FindIterOfSearch_billing *data = (FindIterOfSearch_billing *) findData;
    GtkTreeModel *model = GTK_TREE_MODEL(data->customerList);
    GtkTreeIter *iter = data->result_iter;

    gchar *id_found, *name_found, *numberphone_found, *numberplate_found, *cartype_found;
    gtk_tree_model_get(model, iter, 0, &id_found, -1);
    gtk_tree_model_get(model, iter, 1, &name_found, -1);
    gtk_tree_model_get(model, iter, 2, &numberphone_found, -1);
    gtk_tree_model_get(model, iter, 3, &numberplate_found, -1);
    gtk_tree_model_get(model, iter, 4, &cartype_found, -1);

    // Nếu các label chưa được tạo, tạo mới và gắn vào grid
    if (!data->id_label) {
        data->id_label = gtk_label_new(id_found);
        data->name_label = gtk_label_new(name_found);
        data->numberphone_label = gtk_label_new(numberphone_found);
        data->numberplate_label = gtk_label_new(numberplate_found);
        data->cartype_label = gtk_label_new(cartype_found);

        gtk_grid_attach(GTK_GRID(data->grid), data->id_label, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->name_label, 1, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->numberphone_label, 1, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->numberplate_label, 1, 4, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid), data->cartype_label, 1, 5, 1, 1);
    } else {
        // Cập nhật nội dung của các label
        gtk_label_set_text(GTK_LABEL(data->id_label), id_found);
        gtk_label_set_text(GTK_LABEL(data->name_label), name_found);
        gtk_label_set_text(GTK_LABEL(data->numberphone_label), numberphone_found);
        gtk_label_set_text(GTK_LABEL(data->numberplate_label), numberplate_found);
        gtk_label_set_text(GTK_LABEL(data->cartype_label), cartype_found);
    }

    // Giải phóng bộ nhớ
    g_free(id_found);
    g_free(name_found);
    g_free(numberphone_found);
    g_free(numberplate_found);
    g_free(cartype_found);

    gtk_widget_show_all(data->grid);
}

void search_customerList(gpointer findData, gchar *id_cus)
{
    FindIterOfSearch_billing *data = (FindIterOfSearch_billing *) findData;
    GtkTreeIter iter;

    GtkTreeModel *model = GTK_TREE_MODEL(data->customerList);

    if (gtk_tree_model_get_iter_first(model, &iter))
    {
        do 
        {
            gchar *cell_text;
            gtk_tree_model_get(model, &iter, data->search_column, &cell_text, -1);

            if (g_strcmp0(cell_text, id_cus) == 0)
            {
                *data->result_iter = iter;  // lưu iter vào biến ngoài
                g_free(cell_text);
                display_customer_info_for_payment(data);
                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}

void search_billingList_for_customer(GtkEntry *entry_search, gpointer findData)
{
    FindIterOfSearch_billing *data = (FindIterOfSearch_billing *) findData;
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
                gchar *id_cus;
                gtk_tree_model_get(model, &iter, 2, &id_cus, -1);
                g_free(cell_text);
                search_customerList(data, id_cus);
                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}

void display_payment_info(FindIterOfSearch_billing *findData, gchar *id_bil, gchar *id_ser, gchar *ser_name,
                                                            gchar *cost, gchar *time)
{
    FindIterOfSearch_billing *data = (FindIterOfSearch_billing *) findData;

    // Nếu các label chưa được tạo, tạo mới và gắn vào grid
    if (!data->id_ser_label) {
        data->id_ser_label = gtk_label_new(id_ser);
        data->ser_name_label = gtk_label_new(ser_name);
        data->cost_label = gtk_label_new(cost);
        data->time_label = gtk_label_new(time);

        gtk_grid_attach(GTK_GRID(data->grid_pay), data->id_ser_label, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid_pay), data->ser_name_label, 1, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid_pay), data->cost_label, 1, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(data->grid_pay), data->time_label, 1, 4, 1, 1);
    } else {
        // Cập nhật nội dung của các label
        gtk_label_set_text(GTK_LABEL(data->id_ser_label), id_ser);
        gtk_label_set_text(GTK_LABEL(data->ser_name_label), ser_name);
        gtk_label_set_text(GTK_LABEL(data->cost_label), cost);
        gtk_label_set_text(GTK_LABEL(data->time_label), time);
    }

    // Giải phóng bộ nhớ
    g_free(id_ser);
    g_free(ser_name);
    g_free(cost);
    g_free(time);

    gtk_widget_show_all(data->grid_pay);
}

void search_serviceList(gpointer findData, gchar *id_ser, gchar *id_bil, gchar *time)
{
    FindIterOfSearch_billing *data = (FindIterOfSearch_billing *) findData;
    GtkTreeIter iter;

    GtkTreeModel *model = GTK_TREE_MODEL(data->serviceList);

    if (gtk_tree_model_get_iter_first(model, &iter))
    {
        do 
        {
            gchar *cell_text;
            gtk_tree_model_get(model, &iter, data->search_column, &cell_text, -1);

            if (g_strcmp0(cell_text, id_ser) == 0)
            {
                gchar *ser_name;
                gchar *cost;
                gtk_tree_model_get(model, &iter, 1, &ser_name, -1);
                gtk_tree_model_get(model, &iter, 2, &cost, -1);
                g_free(cell_text);
                display_payment_info(data, id_bil, id_ser, ser_name, cost, time);
                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}

void search_billingList_for_service(GtkEntry *entry_search, gpointer findData)
{
    FindIterOfSearch_billing *data = (FindIterOfSearch_billing *) findData;
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
                gchar *id_bil;
                gchar *time;
                gchar *id_ser;
                gtk_tree_model_get(model, &iter, 0, &id_bil, -1);
                gtk_tree_model_get(model, &iter, 1, &time, -1);
                gtk_tree_model_get(model, &iter, 3, &id_ser, -1);
                g_free(cell_text);
                search_serviceList(data, id_ser, id_bil, time);
                return;
            }

            g_free(cell_text);
        } while (gtk_tree_model_iter_next(model, &iter));
    }
}