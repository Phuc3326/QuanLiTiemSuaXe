// Features for Service page

#include <stdio.h>
#include <gtk/gtk.h>
#include "services.h"
#include "components/label.h"
#include "components/box.h"
#include "components/search.h"
#include "components/grid.h"
#include "components/button.h"
#include "components/scrolled.h"

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

    // Thêm dữ liệu vào file services.txt
    // Mở file
    FILE *file_pointer = fopen(filename, "w");

    // Nếu không mở được file thì thoát
    if (!file_pointer) return;

    // Lấy con trỏ đến hàng đầu tiên trong Listore
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);

    // Lấy dữ liệu từ liststore rồi ghi file
    while (valid)
    {
    const char *id, *name, *cost;
    gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                        0, &id,
                        1, &name,
                        2, &cost,
                        -1);
    fprintf(file_pointer, "%s|%s|%s\n", id, name, cost);
    valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
    }

    // Đóng file
    fclose(file_pointer);
}

static void on_save_clicked(GtkButton *button, gpointer add_data) {
    // Lấy các giá trị đã nhập
    AddServiceData *data = (AddServiceData *)add_data;
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(data->id_entry));
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(data->name_entry));
    const gchar *cost = gtk_entry_get_text(GTK_ENTRY(data->cost_entry));

    // Thêm dữ liệu vào Liststore và vào file
    addData(data->store, "../database/services.txt",
        0, id,
        1, name,
        2, cost,
        -1);

    g_free(data);

    // Đóng cửa sổ sau khi lưu dữ liệu
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window);
}

// Feature add infomation of Services
void addServices(GtkWidget *widget, gpointer user_data) {
    ServiceData *data = (ServiceData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *addServices_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(addServices_window), "Thêm dịch vụ");
    gtk_window_set_transient_for(GTK_WINDOW(addServices_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(addServices_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(addServices_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(addServices_window), GTK_WIN_POS_CENTER);

    // Tạo Grid
    GtkWidget *grid = createGrid(addServices_window);

    // Tạo các label
    GtkWidget *id_label = gtk_label_new("Mã DV:");
    GtkWidget *name_label = gtk_label_new("Tên dịch vụ:");
    GtkWidget *cost_label = gtk_label_new("Giá:");

    // Đặt các label vào grid
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cost_label, 0, 2, 1, 1);

    // Tạo các entry
    GtkWidget *id_entry =  gtk_search_entry_new();
    GtkWidget *name_entry =  gtk_search_entry_new();
    GtkWidget *cost_entry =  gtk_search_entry_new();

    // Đặt các entry vào grid
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), cost_entry, 1, 2, 2, 1);

    // Tạo box chứa nút
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_grid_attach(GTK_GRID(grid), box, 0, 3, 3, 1);

    // Tạo các nút CANCEL và SAVE
    GtkWidget *cancel_button = createButton(box, "CANCEL");
    GtkWidget *save_button = createButton(box, "SAVE");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(addServices_window);

    // Handle SAVE button
    AddServiceData *add_data = g_new(AddServiceData, 1);
    add_data->id_entry = id_entry;
    add_data->name_entry = name_entry;
    add_data->cost_entry = cost_entry;
    add_data->store = data->store;

    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_clicked), add_data);

    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), addServices_window);
}

void deleteServices(GtkWidget *widget, gpointer user_data)
{
    ServiceData *data = (ServiceData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *deleteServices_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(deleteServices_window), "Xóa dịch vụ");
    gtk_window_set_transient_for(GTK_WINDOW(deleteServices_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(deleteServices_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(deleteServices_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(deleteServices_window), GTK_WIN_POS_CENTER);

    // Thiết lập các box trong cửa sổ
    GtkWidget *box_big = createBox(deleteServices_window, GTK_ORIENTATION_VERTICAL, 10); // Box lớn chứa 3 box con
    GtkWidget *box_entry = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thanh tìm kiếm
    GtkWidget *box_information = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thông tin của khách hàng tìm kiếm
    GtkWidget *box_delete = createBox(box_big, GTK_ORIENTATION_VERTICAL, 10); // Box chứa nút cancel và delete

    // Thiết lập cho box_entry
    GtkWidget *label = createLabel(box_entry, "Nhập vào tên dịch vụ");
    GtkWidget *entry = createSearch(box_entry);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Nhập chính xác tên dịch vụ muốn xóa");
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 80);
    GtkWidget *find_button = createButton(box_entry, "Tìm");

    // Thiết lập cho box_information
    GtkWidget *grid = createGrid(box_information);

    GtkWidget *id_label = gtk_label_new("Mã DV:");
    GtkWidget *name_label = gtk_label_new("Tên DV:");
    GtkWidget *cost_label = gtk_label_new("Giá:");

    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cost_label, 0, 2, 1, 1);

    // Xử lí lấy thông tin từ Liststore để hiển thị

    // Thiết lập cho box_delete
    GtkWidget *confirm_label = createLabel(box_delete, "Bạn có chắc chắn muốn xóa dịch vụ này?");
    GtkWidget *confirm_box = createBox(box_delete, GTK_ORIENTATION_HORIZONTAL, 40);
    gtk_widget_set_halign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều ngang
    gtk_widget_set_valign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều dọc
    GtkWidget *cancel_button = createButton(confirm_box, "CANCEL");
    GtkWidget *delete_button = createButton(confirm_box, "DELETE");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(deleteServices_window);

    // Handle DELETE button

    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), deleteServices_window);
}

void editServices(GtkWidget *widget, gpointer user_data)
{
    ServiceData *data = (ServiceData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *editServices_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(editServices_window), "Sửa dịch vụ");
    gtk_window_set_transient_for(GTK_WINDOW(editServices_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(editServices_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(editServices_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(editServices_window), GTK_WIN_POS_CENTER);

    // Thiết lập các box trong cửa sổ
    GtkWidget *box_big = createBox(editServices_window, GTK_ORIENTATION_VERTICAL, 10); // Box lớn chứa 3 box con
    GtkWidget *box_entry = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thanh tìm kiếm
    GtkWidget *box_information = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thông tin của khách hàng tìm kiếm
    GtkWidget *box_edit = createBox(box_big, GTK_ORIENTATION_VERTICAL, 10); // Box chứa nút cancel và edit

    // Thiết lập cho box_entry
    GtkWidget *label = createLabel(box_entry, "Nhập vào tên dịch vụ:");
    GtkWidget *entry = createSearch(box_entry);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Nhập chính xác tên dịch vụ muốn chỉnh sửa");
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 80);
    GtkWidget *find_button = createButton(box_entry, "Tìm");

    // Thiết lập cho box_information
    GtkWidget *grid = createGrid(box_information);

    GtkWidget *id_label = gtk_label_new("Mã DV:");
    GtkWidget *name_label = gtk_label_new("Tên DV:");
    GtkWidget *cost_label = gtk_label_new("Giá:");

    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cost_label, 0, 2, 1, 1);

    GtkWidget *id_entry =  gtk_search_entry_new();
    GtkWidget *name_entry =  gtk_search_entry_new();
    GtkWidget *cost_entry =  gtk_search_entry_new();

    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), cost_entry, 1, 2, 2, 1);

    gtk_widget_set_hexpand(id_entry, TRUE);
    gtk_widget_set_halign(id_entry, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(name_entry, TRUE);
    gtk_widget_set_halign(name_entry, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(cost_entry, TRUE);
    gtk_widget_set_halign(cost_entry, GTK_ALIGN_FILL);

    // Xử lí lấy thông tin từ Liststore để hiển thị

    // Thiết lập cho box_edit
    GtkWidget *confirm_label = createLabel(box_edit, "Bạn có chắc chắn muốn chỉnh sửa dịch vụ này?");
    GtkWidget *confirm_box = createBox(box_edit, GTK_ORIENTATION_HORIZONTAL, 40);
    gtk_widget_set_halign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều ngang
    gtk_widget_set_valign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều dọc
    GtkWidget *cancel_button = createButton(confirm_box, "CANCEL");
    GtkWidget *edit_button = createButton(confirm_box, "EDIT");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(editServices_window);

    // Handle EDIT button

    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), editServices_window);
}
