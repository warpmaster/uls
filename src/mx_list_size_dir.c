#include "uls.h"

int mx_list_size_dir(t_list_dir *list, int *max_len) {
    int size = 0;

    for (t_list_dir *w = list; w != NULL; w = w->next) {
        int len = mx_strlen(w->d_name);

        size++;
        if( len > *max_len)
            *max_len = len;
    }
    return size;
}
