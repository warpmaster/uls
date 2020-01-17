#include "uls.h"

static fptr factory(t_flags *opts);

t_list_dir *mx_sort_list_dir(t_list_dir *lst, t_flags *opts) {
    fptr mx_cmp; 

    if (!lst || !opts)
        return NULL;
    mx_cmp = factory(opts);
    for (t_list_dir *i = lst; i != NULL; i = i->next) {
        for (t_list_dir *j = i->next; j != NULL; j = j->next) {
            mx_cmp(i, j, opts);
        }
    }
    return lst;
}

static fptr factory(t_flags *opts) {
    if (opts->using_r) {
        if (opts->using_S)
            return mx_cmp_size_desc;
        if (opts->using_t)
            return mx_cmp_t_mod_desc;
        return mx_cmp_lex_desc;
    } 
    else {
        if (opts->using_S)
            return mx_cmp_size_asc;
        if (opts->using_t)
            return mx_cmp_t_mod_asc;
        return mx_cmp_lex_asc;
    }
}

void mx_swap(t_list_dir *first, t_list_dir *second) {
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

struct timespec mx_get_time_type(t_list_dir *node, t_flags *opts) {
    if (opts->using_u)
        return node->statbuf->st_atimespec;
    if (opts->using_c)
        return node->statbuf->st_ctimespec;
    return node->statbuf->st_mtimespec;
}
