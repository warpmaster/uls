#include "uls.h"

static fptr factory(t_flags *opts);

t_list_dir *mx_sort_list_dir(t_list_dir *lst, t_flags *opts) {
    fptr cmp; 

    if (!lst || !opts)
        return NULL;
    cmp = factory(opts);
    for (t_list_dir *i = lst; i != NULL; i = i->next) {
        for (t_list_dir *j = i->next; j != NULL; j = j->next) {
            cmp(i, j, opts);
        }
    }
    return lst;
}

static fptr factory(t_flags *opts) {
    if (opts->using_r) {
        if (opts->using_S)
            return cmp_size_desc;
        if (opts->using_t)
            return cmp_t_mod_desc;
        return cmp_lex_desc;
    } 
    else {
        if (opts->using_S)
            return cmp_size_asc;
        if (opts->using_t)
            return cmp_t_mod_asc;
        return cmp_lex_asc;
    }
}

void swap(t_list_dir *first, t_list_dir *second) {
    struct stat *temp_stat = first->statbuf;
    char *temp_name = first->d_name;
    char *temp_path = first->path;

    first->d_name = second->d_name;
    second->d_name = temp_name;
    first->path = second->path;
    second->path = temp_path;
    first->statbuf = second->statbuf;
    second->statbuf = temp_stat;
}

time_t get_time_type(t_list_dir *node, t_flags *opts) {
    if (opts->using_u)
        return node->statbuf->st_atime;
    if (opts->using_c)
        return node->statbuf->st_ctime;
    return node->statbuf->st_mtime;
}
