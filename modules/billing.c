// Features for billing page

#include <stdio.h>
#include <gtk/gtk.h>
#include "billing.h"
#include "components/label.h"
#include "components/box.h"
#include "components/search.h"
#include "components/grid.h"
#include "components/button.h"
#include "components/scrolled.h"
#include "../ui/utils/get_last_iter.h"
#include "../ui/utils/update_txt_bil.h"
#include "../ui/utils/search_in_model.h"
#include "../ui/utils/freeMemory.h"

/**
 * Thêm dữ liệu vào list store
 * @param store List store
 * @param ...args Các dữ liệu
 * @param filename tên của file text cần ghi thông tin
 */
static void addData(GtkListStore *store, const char *filename, ...)
{
    // Thêm dữ liệu vào ListStore
    va_list args;
    va_start(args, filename);

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set_valist(store, &iter, args);

    va_end(args);

    // Thêm dữ liệu vào file bills.txt
    updateTXT_bil(store, filename);
}

static void on_create_clicked(GtkButton *button, gpointer add_data) {
    // Lấy các giá trị đã nhập
    AddBillData *data = (AddBillData *)add_data;
    // Tạo id cho hóa đơn mới tạo
        // Lấy id của hóa cuối cùng của Liststore
        gchar *last_id;
        GtkTreeIter last_iter; 
        get_last_iter(GTK_TREE_MODEL(data->store), &last_iter);
        gtk_tree_model_get(GTK_TREE_MODEL(data->store), &last_iter, 0, &last_id, -1);
        // Tạo id mới nhất
        const gchar *prefix = "B";
        int number = atoi(last_id + strlen(prefix)); /* last_id là con trỏ tới id => +1 thì con trỏ sẽ dịch về sau 1 
        phần tử => trỏ tới "00x". atoi là hàm biến chuỗi số thành số nguyên => lấy được 00x = x */ 
        number++;
        gchar new_id[10];
        g_snprintf(new_id, sizeof(new_id), "%s%03d", prefix, number);

    // Lấy các giá trị đã nhập
    // const gchar *id = gtk_entry_get_text(GTK_ENTRY(data->id_entry));
    const gchar *time = gtk_entry_get_text(GTK_ENTRY(data->time_entry));
    const gchar *id_cus = gtk_entry_get_text(GTK_ENTRY(data->id_cus_entry));
    const gchar *id_ser = gtk_entry_get_text(GTK_ENTRY(data->id_ser_entry));

    // Thêm dữ liệu vào Liststore và vào file
    addData(data->store, "../database/bills.txt",
        0, new_id,
        1, time,
        2, id_cus,
        3, id_ser,
        -1);

    // Đóng cửa sổ sau khi lưu dữ liệu
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window);
}

// Feature add infomation of customers
void addBill(GtkWidget *widget, gpointer user_data) {
    BillData *data = (BillData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *addBill_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(addBill_window), "Tạo hóa đơn");
    gtk_window_set_transient_for(GTK_WINDOW(addBill_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(addBill_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(addBill_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(addBill_window), GTK_WIN_POS_CENTER);

    // Tạo Grid
    GtkWidget *grid = createGrid(addBill_window);

    // Tạo các label
    // GtkWidget *id_billing = gtk_label_new("Mã hóa đơn");
    GtkWidget *time_billing = gtk_label_new("Thời gian");
    GtkWidget *id_customers = gtk_label_new("Mã KH:");
    GtkWidget *id_services = gtk_label_new("Mã DV:");

    // Đặt các label vào grid
    // gtk_grid_attach(GTK_GRID(grid), id_billing, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), time_billing, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_customers, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_services, 0, 3, 1, 1);

    // Tạo các entry
    // GtkWidget *id_bil_entry =  gtk_search_entry_new();
    GtkWidget *time_entry =  gtk_search_entry_new();
    GtkWidget *id_cus_entry =  gtk_search_entry_new();
    GtkWidget *id_ser_entry =  gtk_search_entry_new();

    // Đặt các entry vào grid
    // gtk_grid_attach(GTK_GRID(grid), id_bil_entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), time_entry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), id_cus_entry, 1, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), id_ser_entry, 1, 3, 2, 1);

    // Tạo box chứa nút
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_grid_attach(GTK_GRID(grid), box, 0, 4, 3, 1);

    // Tạo các nút CANCEL và CREATE
    GtkWidget *cancel_button = createButton(box, "CANCEL");
    GtkWidget *create_button = createButton(box, "CREATE");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(addBill_window);

    // Handle CREATE button
    AddBillData *add_data = g_new(AddBillData, 1);
    // add_data->id_entry = id_bil_entry;
    add_data->time_entry = time_entry;
    add_data->id_cus_entry = id_cus_entry;
    add_data->id_ser_entry = id_ser_entry;
    add_data->store = data->store;

    g_signal_connect(create_button, "clicked", G_CALLBACK(on_create_clicked), add_data);

    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), addBill_window);

    g_signal_connect(addBill_window, "destroy", G_CALLBACK(free_memory_when_main_window_destroy), add_data);
}

void exportBill(GtkWidget *widget, gpointer user_data)
{
    BillData *data = (BillData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *exportBill_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(exportBill_window), "Xuất hóa đơn");
    gtk_window_set_transient_for(GTK_WINDOW(exportBill_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(exportBill_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(exportBill_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(exportBill_window), GTK_WIN_POS_CENTER);

    // Thiết lập các box trong cửa sổ
    GtkWidget *box_big = createBox(exportBill_window, GTK_ORIENTATION_VERTICAL, 10); // Box lớn chứa 3 box con
    GtkWidget *box_entry = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thanh tìm kiếm
    GtkWidget *box_information = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thông tin của khách hàng tìm kiếm
    GtkWidget *box_export = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa nút xuất hóa đơn

    // Thiết lập cho box_entry
    GtkWidget *label = createLabel(box_entry, "Nhập vào mã hóa đơn:");
    GtkWidget *entry = createSearch(box_entry);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Nhập chính xác mã hóa đơn muốn xuất");
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 80);

    // Thiết lập cho box_information
    // box_information gồm một grid bên trái hiện thông tin khách hàng và grid bên phải hiện thông tin thanh toán

    // Grid thông tin
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(box_information), grid, TRUE, TRUE, 0);

    GtkWidget *left_title = gtk_label_new("Thông tin khách hàng:");
    GtkWidget *id_label = gtk_label_new("Mã KH:");
    GtkWidget *name_label = gtk_label_new("Tên KH:");
    GtkWidget *numberphone_label = gtk_label_new("SĐT:");
    GtkWidget *numberplate_label = gtk_label_new("Biển số:");
    GtkWidget *cartype_label = gtk_label_new("Loại xe:");

    gtk_grid_attach(GTK_GRID(grid), left_title, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberphone_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberplate_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cartype_label, 0, 5, 1, 1);

    // Xử lí lấy thông tin từ Liststore để hiển thị
    FindIterOfSearch_billing *findData = g_new0(FindIterOfSearch_billing, 1);
    findData->list_store = data->store;
    findData->customerList = data->customerList;
    findData->serviceList = data->serviceList;
    findData->search_column = 0;
    findData->result_iter = g_new0(GtkTreeIter, 1);  // cấp phát cho iter
    findData->grid = grid;
    g_signal_connect(entry, "changed", G_CALLBACK(search_billingList_for_customer), findData);

    // Grid thanh toán
    GtkWidget *grid_pay = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid_pay), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid_pay), 10);
    gtk_box_pack_start(GTK_BOX(box_information), grid_pay, TRUE, TRUE, 0);

    GtkWidget *right_title = gtk_label_new("Thông tin thanh toán:");
    GtkWidget *id_services = gtk_label_new("Mã DV:");
    GtkWidget *name_services = gtk_label_new("Tên DV:");
    GtkWidget *cost = gtk_label_new("Giá:");
    GtkWidget *time = gtk_label_new("Thời gian:");

    gtk_grid_attach(GTK_GRID(grid_pay), right_title, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_pay), id_services, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_pay), name_services, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_pay), cost, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_pay), time, 0, 4, 1, 1);

    // Xử lí lấy thông tin từ Liststore để hiển thị
    findData->grid_pay = grid_pay;
    g_signal_connect(entry, "changed", G_CALLBACK(search_billingList_for_service), findData);

    // Thiết lập box_export
    gtk_widget_set_halign(box_export, GTK_ALIGN_CENTER); // Căn giữa theo chiều ngang
    GtkWidget *back_button = createButton(box_export, "BACK");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(exportBill_window);

    // Handle BACK button
    g_signal_connect_swapped(back_button, "clicked", G_CALLBACK(gtk_widget_destroy), exportBill_window);

    // Giải phóng struct
    g_signal_connect(exportBill_window, "destroy", G_CALLBACK(free_struct_and_iter_billing), findData);
}