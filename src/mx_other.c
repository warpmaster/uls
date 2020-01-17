#include "uls.h"

void mx_err_dir(char *path) {
    char **split = mx_strsplit(path, '/');
    int i = mx_count_words(path, '/');

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

bool mx_cmp(void *s1, void *s2) {
    if (mx_strcmp((char*) s1, (char*) s2) > 0) {
        return true;
    }
    return false;
}

void mx_printerror(char *path, int error_no, bool print_header){
    if (print_header) {
        mx_printstr(path);
        mx_printstr(":\n");
    }
    if (error_no != -1)
        mx_err_dir(path);
}

bool mx_is_valid_flag(char *s) {
    bool res;
    static const char *allf = "lC1aAGrRTngucSt";
    
    while(*s) {
        res = false;
        for (int i = 0, j = mx_strlen(allf); i < j; i++) {
            if(*s == allf[i])
                res = true;
        }
        if (res == false) {
            mx_printerr("uls: illegal option -- ");
            write(2, s, 1);
            mx_printerr("\n");
            return false;
        }
        s++;
    }
    return true;
}
