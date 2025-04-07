#include "listStore.h"

/**
 * Tạo list store
 * @param nColumns Số cột
 * @param ... args Các cột
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