#ifndef MODEL_CENTRAL_H
#define MODEL_CENTRAL_H

#include <gtk/gtk.h>

typedef struct
{
    GtkListStore *customerList;
    GtkListStore *serviceList;
    GtkListStore *billingList;
} modelCentral;

#endif