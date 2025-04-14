#include <gtk/gtk.h>
#include "ui.h"
#include "components/notebook.h"
#include "utils/listStore.h"
#include "pages/customer.h"
#include "pages/service.h"
#include "pages/payment.h"
#include "pages/statistical.h"
#include "../model/model_central.h"
#include "utils/freeMemory.h"

/**
 * Tạo giao diện chính
 * @param window Cửa sổ chính
 */
void createUI(GtkWidget *window)
{
    GtkWidget *notebook = createNotebook(window);

    // Tạo Liststore cho các trang
    modelCentral *data = g_new(modelCentral, 1);
    GtkListStore *customerList = createListStore(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkListStore *serviceList = createListStore(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkListStore *billingList= createListStore(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    data->customerList = customerList;
    data->serviceList = serviceList;
    data->billingList = billingList;

    // Tạo các page
    createCustomerPage(notebook, window, data);
    createServicePage(notebook, window, data);
    createPaymentPage(notebook, window, data);
    createStatisticalPage(notebook, window, data);

    // Giải phóng modelCentral khi dừng chương trình
    g_signal_connect(window, "destroy", G_CALLBACK(free_memory_when_main_window_destroy), data);
}

/**
 * Tạo cửa sổ chính
 * @param app Thể hiện ứng dụng
 * @param title Tiêu đề cửa sổ
 * @param width Chiều rộng cửa sổ
 * @param height Chiều cao cửa sổ
 * @return Cửa sổ chính
 */
GtkWidget *createWindow(GtkApplication *app, const char *title, int width, int height)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    // Khởi tạo giao diện
    createUI(window);

    // Hiển thị cửa sổ và tất cả các widget con
    gtk_widget_show_all(window);

    return window;
}
