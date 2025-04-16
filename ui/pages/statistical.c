#include "statistical.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"
#include "../../model/model_central.h"

gdouble get_service_price(GtkListStore *serviceList, const gchar *service_id) {
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(serviceList), &iter);

    while (valid) {
        gchar *id;
        gchar *price_str;
        gdouble price = 0.0;

        gtk_tree_model_get(GTK_TREE_MODEL(serviceList), &iter,
                           0, &id,        // mã dịch vụ
                           2, &price_str, // giá tiền (dạng chuỗi)
                           -1);

        if (g_strcmp0(id, service_id) == 0) {
            if (price_str != NULL)
            {
                price = g_ascii_strtod(price_str, NULL);
            }

            g_free(id);
            g_free(price_str);
            return price;
        }

        g_free(id);
        g_free(price_str);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(serviceList), &iter);
    }

    return 0.0;
}

void populate_stats_tree_store(GtkTreeStore *store, GtkListStore *billingList, GtkListStore *serviceList) {
    GHashTable *year_hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    GHashTable *month_hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    GHashTable *day_hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(billingList), &iter);

    while (valid) {
        gchar *date_str, *service_id;
        gtk_tree_model_get(GTK_TREE_MODEL(billingList), &iter,
                           1, &date_str,  // ngày
                           3, &service_id, // mã dịch vụ
                           -1);

                        // Xóa khoảng trắng thừa trong service_id
                        g_strstrip(service_id);

        gint day, month, year;
        sscanf(date_str, "%d-%d-%d", &day, &month, &year);

        // Lấy giá dịch vụ từ serviceList
        gdouble price = get_service_price(serviceList, service_id);

        gchar *key_year = g_strdup_printf("%d", year);
        gchar *key_month = g_strdup_printf("%d-%02d", year, month);
        gchar *key_day = g_strdup_printf("%d-%02d-%02d", year, month, day);

        GtkTreeIter *year_iter = g_hash_table_lookup(year_hash, key_year);
        if (!year_iter) {
            year_iter = g_new(GtkTreeIter, 1);
            gtk_tree_store_append(store, year_iter, NULL);
            gtk_tree_store_set(store, year_iter,
                               0, key_year,
                               1, 1,
                               2, price,
                               -1);
            g_hash_table_insert(year_hash, key_year, year_iter);
        } else {
            gint car_count;
            gdouble revenue;
            gtk_tree_model_get(GTK_TREE_MODEL(store), year_iter, 1, &car_count, 2, &revenue, -1);
            gtk_tree_store_set(store, year_iter,
                               1, car_count + 1,
                               2, revenue + price,
                               -1);
            g_free(key_year);
        }

        GtkTreeIter *month_iter = g_hash_table_lookup(month_hash, key_month);
        if (!month_iter) {
            month_iter = g_new(GtkTreeIter, 1);
            gtk_tree_store_append(store, month_iter, year_iter);
            gchar *month_label = g_strdup_printf("Tháng %d", month);
            gtk_tree_store_set(store, month_iter,
                               0, month_label,
                               1, 1,
                               2, price,
                               -1);
            g_hash_table_insert(month_hash, key_month, month_iter);
            g_free(month_label);
        } else {
            gint car_count;
            gdouble revenue;
            gtk_tree_model_get(GTK_TREE_MODEL(store), month_iter, 1, &car_count, 2, &revenue, -1);
            gtk_tree_store_set(store, month_iter,
                               1, car_count + 1,
                               2, revenue + price,
                               -1);
            g_free(key_month);
        }

        GtkTreeIter *day_iter = g_hash_table_lookup(day_hash, key_day);
        if (!day_iter) {
            day_iter = g_new(GtkTreeIter, 1);
            gtk_tree_store_append(store, day_iter, month_iter);
            gchar *day_label = g_strdup_printf("Ngày %d", day);
            gtk_tree_store_set(store, day_iter,
                               0, day_label,
                               1, 1,
                               2, price,
                               -1);
            g_hash_table_insert(day_hash, key_day, day_iter);
            g_free(day_label);
        } else {
            gint car_count;
            gdouble revenue;
            gtk_tree_model_get(GTK_TREE_MODEL(store), day_iter, 1, &car_count, 2, &revenue, -1);
            gtk_tree_store_set(store, day_iter,
                               1, car_count + 1,
                               2, revenue + price,
                               -1);
            g_free(key_day);
        }

        g_free(date_str);
        g_free(service_id);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(billingList), &iter);
    }

    g_hash_table_destroy(year_hash);
    g_hash_table_destroy(month_hash);
    g_hash_table_destroy(day_hash);
}

GtkWidget *createStatisticalPage(GtkWidget *notebook, GtkWidget *window, gpointer user_data) {
    GtkWidget *page = createPage(notebook, GTK_ORIENTATION_VERTICAL, 10, "Thống kê & Báo cáo");

    GtkTreeStore *store = gtk_tree_store_new(3,
                                             G_TYPE_STRING,   // Cột 0: Thời gian
                                             G_TYPE_INT,      // Cột 1: Số xe
                                             G_TYPE_DOUBLE);  // Cột 2: Doanh thu

    modelCentral *data = (modelCentral *)user_data;
    populate_stats_tree_store(store, data->billingList, data->serviceList);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                GTK_POLICY_NEVER,
                                GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(page), scrolled_window);

    GtkWidget *statsTreeView = createTreeView(scrolled_window);

    const gchar *columnNames[] = {"Thời gian", "Số xe sửa chữa", "Doanh thu (VND)"};
    createColumns(statsTreeView, columnNames, 3);
    gtk_tree_view_set_model(GTK_TREE_VIEW(statsTreeView), GTK_TREE_MODEL(store));

    return page;
}