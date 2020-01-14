#include "uls.h"

void cmp_lex_asc(t_list_dir *first, t_list_dir *second, 
t_flags *opts) {
    if (mx_strcmp(first->d_name, second->d_name) > 0 && opts) {
        swap(first, second);
    }
}

void cmp_size_asc(t_list_dir *first, t_list_dir *second, 
t_flags *opts) {
    if (first->statbuf->st_size < second->statbuf->st_size && opts) {
        swap(first, second);
        return;
    }
    if (first->statbuf->st_size == second->statbuf->st_size) {
        if (mx_strcmp(first->d_name, second->d_name) > 0) {
            swap(first, second);
            return;
        }
    }
}

void cmp_t_mod_asc(t_list_dir *first, t_list_dir *second, 
t_flags *opts) {
    time_t t1 = get_time_type(first, opts);
    time_t t2 = get_time_type(second, opts);

    if (t1 < t2) {
        swap(first, second);
        return;
    }
    if (t1 == t2) {
        if (mx_strcmp(first->d_name, second->d_name) > 0) {
            swap(first, second);
            return;
        }
    }
}
