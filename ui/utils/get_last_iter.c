#include <gtk/gtk.h>
#include "get_last_iter.h"

void get_last_iter (GtkTreeModel *model, GtkTreeIter *last_iter)
{   
    GtkTreeIter iter;
    if (gtk_tree_model_get_iter_first(model, &iter)) 
    {
        *last_iter = iter;
        while (gtk_tree_model_iter_next(model, &iter)) 
        {
            *last_iter = iter;
        }
    }
}