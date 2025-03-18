#include "listStore.h"

/**
 * Tạo list store
 * @param nColumns Số cột
 * @param ...args Các cột
 * @return GtkListStore
 */
GtkListStore *createListStore(int nColumns, ...)
{
    va_list args;
    va_start(args, nColumns);

    // Array sẽ chứa toàn bộ type của các cột từ "..."
    GType *types = g_malloc(sizeof(GType) * nColumns);

    // Lấy từng type từ "..."
    for (int i = 0; i < nColumns; i++)
    {
        types[i] = va_arg(args, GType);
    }

    // Tạo list store với array các type
    GtkListStore *store = gtk_list_store_newv(nColumns, types);

    // Giải phóng mảng tạm (tránh bị memory leak)
    g_free(types);

    va_end(args);
    return store;
}

/**
 * Thêm iter vào list store
 * @param store List store
 * @param iter Iter
 */
void appendIter(GtkListStore *store, GtkTreeIter *iter)
{
    gtk_list_store_append(store, iter);
}

/**
 * Thêm dữ liệu vào list store
 * @param store List store
 * @param iter Iter
 * @param ...args Các dữ liệu
 */
void addData(GtkListStore *store, GtkTreeIter *iter, ...)
{
    va_list args;
    va_start(args, iter);

    appendIter(store, iter);
    gtk_list_store_set_valist(store, iter, args);

    va_end(args);
}
