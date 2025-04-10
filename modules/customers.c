// Features for customer page

#include <stdio.h>
#include <gtk/gtk.h>
#include "customers.h"
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

    // Thêm dữ liệu vào file customers.txt
    // Mở file
    FILE *file_pointer = fopen(filename, "w");

    // Nếu không mở được file thì thoát
    if (!file_pointer) return;

    // Lấy con trỏ đến hàng đầu tiên trong Listore
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);

    // Lấy dữ liệu từ liststore rồi ghi file
    while (valid)
    {
    const char *id, *name, *numberphone, *numberplate, *cartype;
    gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                        0, &id,
                        1, &name,
                        2, &numberphone,
                        3, &numberplate,
                        4, &cartype,
                        -1);
    fprintf(file_pointer, "%s|%s|%s|%s|%s\n", id, name, numberphone, numberplate, cartype);
    valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
    }

    // Đóng file
    fclose(file_pointer);
}

static void on_save_clicked(GtkButton *button, gpointer add_data) {
    // Lấy các giá trị đã nhập
    AddCustomerData *data = (AddCustomerData *)add_data;
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(data->id_entry));
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(data->name_entry));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(data->phone_entry));
    const gchar *plate = gtk_entry_get_text(GTK_ENTRY(data->plate_entry));
    const gchar *type = gtk_entry_get_text(GTK_ENTRY(data->type_entry));

    // Thêm dữ liệu vào Liststore và vào file
    addData(data->store, "../database/customers.txt",
        0, id,
        1, name,
        2, phone,
        3, plate,
        4, type,
        -1);

    g_free(data);

    // Đóng cửa sổ sau khi lưu dữ liệu
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window);
}

// Feature add infomation of customers
void addCustomers(GtkWidget *widget, gpointer user_data) {
    CustomerData *data = (CustomerData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *addCustomers_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(addCustomers_window), "Thêm khách hàng");
    gtk_window_set_transient_for(GTK_WINDOW(addCustomers_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(addCustomers_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(addCustomers_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(addCustomers_window), GTK_WIN_POS_CENTER);

    // Tạo Grid
    GtkWidget *grid = createGrid(addCustomers_window);

    // Tạo các label
    GtkWidget *id_label = gtk_label_new("Mã KH:");
    GtkWidget *name_label = gtk_label_new("Tên KH:");
    GtkWidget *numberphone_label = gtk_label_new("SĐT:");
    GtkWidget *numberplate_label = gtk_label_new("Biển số:");
    GtkWidget *cartype_label = gtk_label_new("Loại xe:");

    // Đặt các label vào grid
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberphone_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberplate_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cartype_label, 0, 4, 1, 1);

    // Tạo các entry
    GtkWidget *id_entry =  gtk_search_entry_new();
    GtkWidget *name_entry =  gtk_search_entry_new();
    GtkWidget *numberphone_entry =  gtk_search_entry_new();
    GtkWidget *numberplate_entry =  gtk_search_entry_new();
    GtkWidget *cartype_entry =  gtk_search_entry_new();

    // Đặt các entry vào grid
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), numberphone_entry, 1, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), numberplate_entry, 1, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), cartype_entry, 1, 4, 2, 1);

    // Tạo box chứa nút
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_grid_attach(GTK_GRID(grid), box, 0, 5, 3, 1);

    // Tạo các nút CANCEL và SAVE
    GtkWidget *cancel_button = createButton(box, "CANCEL");
    GtkWidget *save_button = createButton(box, "SAVE");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(addCustomers_window);

    // Handle SAVE button
    AddCustomerData *add_data = g_new(AddCustomerData, 1);
    add_data->id_entry = id_entry;
    add_data->name_entry = name_entry;
    add_data->phone_entry = numberphone_entry;
    add_data->plate_entry = numberplate_entry;
    add_data->type_entry = cartype_entry;
    add_data->store = data->store;

    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_clicked), add_data);

    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), addCustomers_window);
}

void deleteCustomers(GtkWidget *widget, gpointer user_data)
{
    CustomerData *data = (CustomerData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *deleteCustomers_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(deleteCustomers_window), "Xóa khách hàng");
    gtk_window_set_transient_for(GTK_WINDOW(deleteCustomers_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(deleteCustomers_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(deleteCustomers_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(deleteCustomers_window), GTK_WIN_POS_CENTER);

    // Thiết lập các box trong cửa sổ
    GtkWidget *box_big = createBox(deleteCustomers_window, GTK_ORIENTATION_VERTICAL, 10); // Box lớn chứa 3 box con
    GtkWidget *box_entry = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thanh tìm kiếm
    GtkWidget *box_information = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thông tin của khách hàng tìm kiếm
    GtkWidget *box_delete = createBox(box_big, GTK_ORIENTATION_VERTICAL, 10); // Box chứa nút cancel và delete

    // Thiết lập cho box_entry
    GtkWidget *label = createLabel(box_entry, "Nhập vào biển số xe:");
    GtkWidget *entry = createSearch(box_entry);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Nhập chính xác biển số muốn xóa");
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 80);
    GtkWidget *find_button = createButton(box_entry, "Tìm");

    // Thiết lập cho box_information
    GtkWidget *grid = createGrid(box_information);

    GtkWidget *id_label = gtk_label_new("Mã KH:");
    GtkWidget *name_label = gtk_label_new("Tên KH:");
    GtkWidget *numberphone_label = gtk_label_new("SĐT:");
    GtkWidget *numberplate_label = gtk_label_new("Biển số:");
    GtkWidget *cartype_label = gtk_label_new("Loại xe:");

    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberphone_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberplate_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cartype_label, 0, 4, 1, 1);

    // Xử lí lấy thông tin từ Liststore để hiển thị

    // Thiết lập cho box_delete
    GtkWidget *confirm_label = createLabel(box_delete, "Bạn có chắc chắn muốn xóa khách hàng này?");
    GtkWidget *confirm_box = createBox(box_delete, GTK_ORIENTATION_HORIZONTAL, 40);
    gtk_widget_set_halign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều ngang
    gtk_widget_set_valign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều dọc
    GtkWidget *cancel_button = createButton(confirm_box, "CANCEL");
    GtkWidget *delete_button = createButton(confirm_box, "DELETE");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(deleteCustomers_window);

    // Handle DELETE button

    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), deleteCustomers_window);
}

void editCustomers(GtkWidget *widget, gpointer user_data)
{
    CustomerData *data = (CustomerData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *editCustomers_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(editCustomers_window), "Sửa khách hàng");
    gtk_window_set_transient_for(GTK_WINDOW(editCustomers_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(editCustomers_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(editCustomers_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(editCustomers_window), GTK_WIN_POS_CENTER);

    // Thiết lập các box trong cửa sổ
    GtkWidget *box_big = createBox(editCustomers_window, GTK_ORIENTATION_VERTICAL, 10); // Box lớn chứa 3 box con
    GtkWidget *box_entry = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thanh tìm kiếm
    GtkWidget *box_information = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thông tin của khách hàng tìm kiếm
    GtkWidget *box_edit = createBox(box_big, GTK_ORIENTATION_VERTICAL, 10); // Box chứa nút cancel và edit

    // Thiết lập cho box_entry
    GtkWidget *label = createLabel(box_entry, "Nhập vào biển số xe:");
    GtkWidget *entry = createSearch(box_entry);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Nhập chính xác biển số muốn chỉnh sửa");
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 80);
    GtkWidget *find_button = createButton(box_entry, "Tìm");

    // Thiết lập cho box_information
    GtkWidget *grid = createGrid(box_information);

    GtkWidget *id_label = gtk_label_new("Mã KH:");
    GtkWidget *name_label = gtk_label_new("Tên KH:");
    GtkWidget *numberphone_label = gtk_label_new("SĐT:");
    GtkWidget *numberplate_label = gtk_label_new("Biển số:");
    GtkWidget *cartype_label = gtk_label_new("Loại xe:");

    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberphone_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberplate_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cartype_label, 0, 4, 1, 1);

    GtkWidget *id_entry =  gtk_search_entry_new();
    GtkWidget *name_entry =  gtk_search_entry_new();
    GtkWidget *numberphone_entry =  gtk_search_entry_new();
    GtkWidget *numberplate_entry =  gtk_search_entry_new();
    GtkWidget *cartype_entry =  gtk_search_entry_new();

    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), numberphone_entry, 1, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), numberplate_entry, 1, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), cartype_entry, 1, 4, 2, 1);
    gtk_widget_set_hexpand(id_entry, TRUE);
    gtk_widget_set_halign(id_entry, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(name_entry, TRUE);
    gtk_widget_set_halign(name_entry, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(numberphone_entry, TRUE);
    gtk_widget_set_halign(numberphone_entry, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(numberplate_entry, TRUE);
    gtk_widget_set_halign(numberplate_entry, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(cartype_entry, TRUE);
    gtk_widget_set_halign(cartype_entry, GTK_ALIGN_FILL);

    // Xử lí lấy thông tin từ Liststore để hiển thị

    // Thiết lập cho box_edit
    GtkWidget *confirm_label = createLabel(box_edit, "Bạn có chắc chắn muốn chỉnh sửa khách hàng này?");
    GtkWidget *confirm_box = createBox(box_edit, GTK_ORIENTATION_HORIZONTAL, 40);
    gtk_widget_set_halign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều ngang
    gtk_widget_set_valign(confirm_box, GTK_ALIGN_CENTER); // Căn giữa theo chiều dọc
    GtkWidget *cancel_button = createButton(confirm_box, "CANCEL");
    GtkWidget *edit_button = createButton(confirm_box, "EDIT");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(editCustomers_window);

    // Handle EDIT button

    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), editCustomers_window);
}

void historyCustomers(GtkWidget *widget, gpointer user_data)
{
    CustomerData *data = (CustomerData *)user_data;

    // Thiết lập cửa sổ
    GtkWidget *historyCustomers_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(historyCustomers_window), "Lịch sử khách hàng");
    gtk_window_set_transient_for(GTK_WINDOW(historyCustomers_window), GTK_WINDOW(data->main_window));  // Gắn vào cửa sổ chính
    gtk_window_set_modal(GTK_WINDOW(historyCustomers_window), TRUE);  // Làm cửa sổ phụ modal
    gtk_window_set_default_size(GTK_WINDOW(historyCustomers_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(historyCustomers_window), GTK_WIN_POS_CENTER);

    // Thiết lập các box trong cửa sổ
    GtkWidget *box_big = createBox(historyCustomers_window, GTK_ORIENTATION_VERTICAL, 10); // Box lớn chứa 3 box con
    GtkWidget *box_entry = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thanh tìm kiếm
    GtkWidget *box_information = createBox(box_big, GTK_ORIENTATION_HORIZONTAL, 10); // Box chứa thông tin của khách hàng tìm kiếm
    GtkWidget *box_back = createBox(box_big, GTK_ORIENTATION_VERTICAL, 10); // Box chứa nút Back

    // Thiết lập cho box_entry
    GtkWidget *label = createLabel(box_entry, "Nhập vào biển số xe:");
    GtkWidget *entry = createSearch(box_entry);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Nhập chính xác biển số muốn xem lịch sử");
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 80);
    GtkWidget *find_button = createButton(box_entry, "Tìm");

    // Thiết lập cho box_information
    // box_information gồm một grid bên trái hiện thông tin khách hàng và box bên phải hiện lịch sử

    // Grid thông tin
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(box_information), grid, TRUE, TRUE, 0);

    GtkWidget *id_label = gtk_label_new("Mã KH:");
    GtkWidget *name_label = gtk_label_new("Tên KH:");
    GtkWidget *numberphone_label = gtk_label_new("SĐT:");
    GtkWidget *numberplate_label = gtk_label_new("Biển số:");
    GtkWidget *cartype_label = gtk_label_new("Loại xe:");

    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberphone_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), numberplate_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cartype_label, 0, 4, 1, 1);

    // Xử lí lấy thông tin từ Liststore để hiển thị
    
    // Box lịch sử
    GtkWidget *box_history =gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(box_information), box_history, TRUE, TRUE, 0);

    GtkWidget *grid_history = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid_history), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid_history), 10);
    gtk_widget_set_hexpand(grid_history, TRUE);   // Cho phép giãn ngang
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_history), TRUE);

    GtkWidget *time_label = gtk_label_new("Thời gian");
    GtkWidget *service_label = gtk_label_new("Dịch vụ");
    GtkWidget *cost_label = gtk_label_new("Giá");

    gtk_grid_attach(GTK_GRID(grid_history), time_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_history), service_label, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_history), cost_label, 2, 0, 1, 1);

    // Tạo thanh cuộn cho grid_history ở trong box_history
    GtkWidget *scrolled = createScrolled(box_history, grid_history);

    // Xử lí lấy lịch sử từ Liststore của tab service

    // Thiết lập box_back
    gtk_widget_set_halign(box_back, GTK_ALIGN_CENTER); // Căn giữa theo chiều ngang
    GtkWidget *back_button = createButton(box_back, "BACK");

    // Hiển thị cửa sổ con
    gtk_widget_show_all(historyCustomers_window);

    g_signal_connect_swapped(back_button, "clicked", G_CALLBACK(gtk_widget_destroy), historyCustomers_window);
}