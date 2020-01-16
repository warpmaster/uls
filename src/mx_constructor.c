#include "uls.h"

t_list_dir *make_dir_list(char *path, t_list_dir *list,
t_flags *opts, int *error_no);
void print_dir_list(char *dir_name, t_list_dir *list, 
t_flags *opts, bool print_header);

/*void */int mx_constructor(t_list_dir *file_list, 
t_list_dir *dir_list, t_flags flag, int files_cnt) {
    int is_err = 0;

    file_list = mx_sort_list_dir(file_list, &flag);
    dir_list = mx_sort_list_dir(dir_list, &flag);
    if (flag.using_l)
        mx_print_l_flag(file_list, &flag, false);
    else if (flag.using_1 || (!isatty(STDOUT_FILENO) && !flag.using_C))
        mx_print_flag_1(file_list, &flag);
    else
        mx_print_table(file_list, &flag);
    for (t_list_dir *w = dir_list; w != NULL; w = w->next) {
        if (dir_list->next == NULL && file_list == NULL && files_cnt == 1)
            directory_walker(w->path, &flag, false, &is_err);
        else {
            if (w != dir_list || file_list != NULL)
                mx_printchar('\n');
            directory_walker(w->path, &flag, true, &is_err);
        }
    }
    mx_delete_list_dir(&file_list);
    mx_delete_list_dir(&dir_list);

    return is_err;
}

void directory_walker(char *path, t_flags *opts, bool print_header, int *is_err) {
    t_list_dir *list = NULL;
    int error_no = -1;

    list = make_dir_list(path, list, opts, &error_no);
    if (error_no == -1)
        print_dir_list(path, list, opts, print_header); 
    else
        *is_err = 1;
    if (opts->using_R) {
        for (t_list_dir *w = list; w != NULL; w = w->next) {
            if (mx_get_file_type(w->statbuf->st_mode) == 'd' 
            && !(mx_strcmp(w->d_name, ".") == 0 
            || mx_strcmp(w->d_name, "..") == 0)) {
                mx_printchar('\n');
                directory_walker(w->path, opts, true, is_err);
            }
        }
    }
    mx_delete_list_dir(&list);
}

t_list_dir *make_dir_list(char *path, t_list_dir *list,
t_flags *opts, int *error_no) {
    DIR *dir = NULL;
    struct dirent *entry;

    dir = opendir(path);
    if (!dir) {
        err_dir(path, error_no);
        return NULL;
    }
    while ((entry = readdir(dir)) != NULL)
        if (!(!opts->using_a && entry->d_name[0] == '.') 
        || (opts->using_A && !(mx_strcmp(entry->d_name, ".") == 0 
        || mx_strcmp(entry->d_name, "..") == 0)))
            mx_push_back_dir(&list, entry->d_name, path);
    closedir(dir);
    list = mx_sort_list_dir(list, opts);
    return list;
}

void print_dir_list(char *dir_name, t_list_dir *list, 
t_flags *opts, bool print_header) {
    if (print_header) {
        mx_printstr(dir_name);
        mx_printstr(":\n");
    }
    if (opts->using_l && list)
        mx_print_l_flag(list, opts, true);
    else if (opts->using_1 || (!isatty(STDOUT_FILENO) && !opts->using_C))
        mx_print_flag_1(list, opts);
    else
        mx_print_table(list, opts);
}
