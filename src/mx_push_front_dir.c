#include "uls.h"

void mx_push_front_dir(t_list_dir **list, const char *d_name, 
const char *path) {
    t_list_dir *new_node = mx_create_node_dir(d_name, path);
    new_node->next = *list;
    *list = new_node;
}
