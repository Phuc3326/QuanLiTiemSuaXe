#include "statistical.h"
#include "../components/box.h"
#include "../components/button.h"
#include "../components/treeView.h"
#include "../components/search.h"
#include "../components/page.h"
#include "../utils/listStore.h"

/**
 * Tạo trang thống kê
 * @param notebook Notebook chứa trang thống kê
 * @return Trang thống kê
 */
GtkWidget *createStatisticalPage(GtkWidget *notebook)
{
    // Tạo trang thống kê
    GtkWidget *page = createPage(notebook, GTK_ORIENTATION_VERTICAL, 10, "Thống kê & Báo cáo");

    // Tạo box tổng quan
    GtkWidget *overviewBox = createBox(page, GTK_ORIENTATION_HORIZONTAL, 20);

    GtkWidget *totalCarsLabel = gtk_label_new("Tổng số xe đã sửa chữa: 100000");
    gtk_widget_set_halign(totalCarsLabel, GTK_ALIGN_START);

    GtkWidget *totalRevenueLabel = gtk_label_new("Doanh thu tháng này: 1,000,000 VND");
    gtk_widget_set_halign(totalRevenueLabel, GTK_ALIGN_END);

    gtk_box_pack_start(GTK_BOX(overviewBox), totalCarsLabel, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(overviewBox), totalRevenueLabel, TRUE, TRUE, 10);

    // Tạo bảng danh sách thống kê
    GtkWidget *statsTreeView = createTreeView(page);
    const gchar *columnNames[] = {"Ngày", "Số xe sửa chữa", "Doanh thu (VND)"};
    createColumns(statsTreeView, columnNames, 3);

    // Gán dữ liệu mẫu
    GtkListStore *statsList = createListStore(3, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
    GtkTreeIter iter;

    addData(statsList, &iter, 0, "01/03/2024", 1, 120, 2, "1,200,000 VND", -1);
    addData(statsList, &iter, 0, "02/03/2024", 1, 95, 2, "950,000 VND", -1);

    gtk_tree_view_set_model(GTK_TREE_VIEW(statsTreeView), GTK_TREE_MODEL(statsList));

    return page;
}
