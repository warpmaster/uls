#include "uls.h"

void mx_delete_list_dir(t_list_dir **head) {
    t_list_dir *w = *head;

    while (w != NULL) {
        t_list_dir *temp = w;
        w = w->next;

        free(temp->d_name);
        free(temp->path);
        free(temp->statbuf);
        free(temp);
    }
    *head = NULL;
}
