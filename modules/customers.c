#include <gtk/gtk.h>
#include "customers.h"
#include "components/label.h"
#include "components/box.h"
#include "components/search.h"
#include "components/grid.h"
#include "components/button.h"

void addCustomers(GtkWidget *widget, gpointer window_parent) {
    GtkWidget *addCustomers_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(addCustomers_window), "Thêm khách hàng");
    gtk_window_set_transient_for(GTK_WINDOW(addCustomers_window), GTK_WINDOW(window_parent));  // Gắn vào cửa sổ chính
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
}