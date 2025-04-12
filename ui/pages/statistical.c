#include "statistical.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"

// Các cột trong Treestore
enum {
    COL_LABEL,
    COL_TOTAL_CARS,
    COL_REVENUE,
    NUM_COLS
};

/**
 * Tạo trang thống kê
 * @param notebook Notebook chứa trang thống kê
 * @return Trang thống kê
 */
GtkWidget *createStatisticalPage(GtkWidget *notebook, GtkWidget *window)
{
    // Tạo trang thống kê
    GtkWidget *page = createPage(notebook, GTK_ORIENTATION_VERTICAL, 10, "Thống kê & Báo cáo");

    // Tạo box tổng quan
    GtkWidget *overviewBox = createBox(page, GTK_ORIENTATION_HORIZONTAL, 20);

    // Tạo Treestore
    GtkTreeStore *store = gtk_tree_store_new(NUM_COLS,
        G_TYPE_STRING,   // Cột 0: Label
        G_TYPE_INT,      // Cột 1: Số xe
        G_TYPE_DOUBLE);  // Cột 2: Doanh thu

    GtkTreeIter year_iter, month_iter, day_iter;

    // ===== Năm 2025 =====
    gtk_tree_store_append(store, &year_iter, NULL);
    gtk_tree_store_set(store, &year_iter,
                    COL_LABEL, "2025",
                    COL_TOTAL_CARS, 200,
                    COL_REVENUE, 500000000.0,
                    -1);

    // Tháng 4
    gtk_tree_store_append(store, &month_iter, &year_iter);
    gtk_tree_store_set(store, &month_iter,
                    COL_LABEL, "Tháng 4",
                    COL_TOTAL_CARS, 50,
                    COL_REVENUE, 120000000.0,
                    -1);

    // Ngày 10
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 10",
                    COL_TOTAL_CARS, 5,
                    COL_REVENUE, 12000000.0,
                    -1);

    // Ngày 15
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 15",
                    COL_TOTAL_CARS, 7,
                    COL_REVENUE, 16000000.0,
                    -1);

    // Tháng 5
    gtk_tree_store_append(store, &month_iter, &year_iter);
    gtk_tree_store_set(store, &month_iter,
                    COL_LABEL, "Tháng 5",
                    COL_TOTAL_CARS, 60,
                    COL_REVENUE, 130000000.0,
                    -1);

    // Ngày 5
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 5",
                    COL_TOTAL_CARS, 6,
                    COL_REVENUE, 15000000.0,
                    -1);

    // Ngày 20
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 20",
                    COL_TOTAL_CARS, 8,
                    COL_REVENUE, 18000000.0,
                    -1);


    // ===== Năm 2024 =====
    gtk_tree_store_append(store, &year_iter, NULL);
    gtk_tree_store_set(store, &year_iter,
                    COL_LABEL, "2024",
                    COL_TOTAL_CARS, 180,
                    COL_REVENUE, 450000000.0,
                    -1);

    // Tháng 3
    gtk_tree_store_append(store, &month_iter, &year_iter);
    gtk_tree_store_set(store, &month_iter,
                    COL_LABEL, "Tháng 3",
                    COL_TOTAL_CARS, 40,
                    COL_REVENUE, 100000000.0,
                    -1);

    // Ngày 1
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 1",
                    COL_TOTAL_CARS, 4,
                    COL_REVENUE, 10000000.0,
                    -1);

    // Ngày 18
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 18",
                    COL_TOTAL_CARS, 9,
                    COL_REVENUE, 20000000.0,
                    -1);

    // Tháng 6
    gtk_tree_store_append(store, &month_iter, &year_iter);
    gtk_tree_store_set(store, &month_iter,
                    COL_LABEL, "Tháng 6",
                    COL_TOTAL_CARS, 55,
                    COL_REVENUE, 120000000.0,
                    -1);

    // Ngày 8
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 8",
                    COL_TOTAL_CARS, 6,
                    COL_REVENUE, 14000000.0,
                    -1);

    // Ngày 22
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 22",
                    COL_TOTAL_CARS, 10,
                    COL_REVENUE, 22000000.0,
                    -1);


    // ===== Năm 2023 =====
    gtk_tree_store_append(store, &year_iter, NULL);
    gtk_tree_store_set(store, &year_iter,
                    COL_LABEL, "2023",
                    COL_TOTAL_CARS, 190,
                    COL_REVENUE, 470000000.0,
                    -1);

    // Tháng 2
    gtk_tree_store_append(store, &month_iter, &year_iter);
    gtk_tree_store_set(store, &month_iter,
                    COL_LABEL, "Tháng 2",
                    COL_TOTAL_CARS, 45,
                    COL_REVENUE, 110000000.0,
                    -1);

    // Ngày 2
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 2",
                    COL_TOTAL_CARS, 5,
                    COL_REVENUE, 11000000.0,
                    -1);

    // Ngày 14
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 14",
                    COL_TOTAL_CARS, 6,
                    COL_REVENUE, 13000000.0,
                    -1);

    // Tháng 9
    gtk_tree_store_append(store, &month_iter, &year_iter);
    gtk_tree_store_set(store, &month_iter,
                    COL_LABEL, "Tháng 9",
                    COL_TOTAL_CARS, 70,
                    COL_REVENUE, 150000000.0,
                    -1);

    // Ngày 7
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 7",
                    COL_TOTAL_CARS, 8,
                    COL_REVENUE, 16000000.0,
                    -1);

    // Ngày 30
    gtk_tree_store_append(store, &day_iter, &month_iter);
    gtk_tree_store_set(store, &day_iter,
                    COL_LABEL, "Ngày 30",
                    COL_TOTAL_CARS, 9,
                    COL_REVENUE, 19000000.0,
                    -1);

    // Tạo bảng danh sách thống kê
    GtkWidget *statsTreeView = createTreeView(page);
    const gchar *columnNames[] = {"Thời gian", "Số xe sửa chữa", "Doanh thu (VND)"};
    createColumns(statsTreeView, columnNames, 3);
    gtk_tree_view_set_model(GTK_TREE_VIEW(statsTreeView), GTK_TREE_MODEL(store));

    return page;
}
