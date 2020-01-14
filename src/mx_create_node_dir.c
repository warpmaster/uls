#include "uls.h"

t_list_dir *mx_create_node_dir(const char *d_name, const char *path) {
    t_list_dir *node = (t_list_dir *)malloc(sizeof(t_list_dir));
    char *path_w_slash = NULL;

    if (!node)
        return NULL;
    node->d_name = mx_strdup(d_name);
    if (path) {
        if (mx_strcmp(path, "/") != 0)
            path_w_slash = mx_strjoin(path, "/");
        else
            path_w_slash = mx_strdup("/");
    }
    node->path = mx_strjoin(path_w_slash, d_name);
    node->statbuf = (struct stat *)malloc(sizeof(struct stat));
    lstat(node->path, node->statbuf);
    node->next = NULL;
    free(path_w_slash);
    return node;
}
