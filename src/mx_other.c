#include "uls.h"

void err_dir(char *path, int *error_no){
    char **split = mx_strsplit(path, '/');
    int i = mx_count_words(path, '/');

    // если выводить только один путь к директории с ограниченным доступом, то печатается лишний путь
    *error_no = errno;
    mx_printstr(path);
    mx_printstr(":\n");
    mx_printerr("uls: ");
    perror(split[i-1]);

    for (int j = 0; j < i; j++) {
        free(split[j]);
    }
    free(split);
}

void mx_print_bad_list(t_list *lst) {
    while (lst) {
        mx_printerr("uls: ");
        mx_printerr((char*)lst->data);
        mx_printerr(": No such file or directory\n");
        lst = lst->next;
    }
}

bool cmp(void *s1, void *s2) {
    if (mx_strcmp((char*) s1, (char*) s2) > 0) {
        return true;
    }
    return false;
}
