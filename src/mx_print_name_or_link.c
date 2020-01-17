#include "uls.h"

static char *get_link(t_list_dir *node, t_flags *fl);

void mx_print_name_or_link(t_list_dir *w, t_flags *fl){
    char *link = NULL;

    if (mx_get_file_type(w->statbuf->st_mode) == 'l') {
        link = get_link(w, fl);
        mx_printstr(link);
        free(link);
    } 
    else {
        fl->using_G ? mx_print_G_flag(w->d_name, w->statbuf->st_mode) 
        : mx_printstr(w->d_name);
    }
    mx_printchar('\n');
}

static char *get_link(t_list_dir *node, t_flags *fl) {
    char buf[256];
    char *res = NULL;

    mx_memset(buf, '\0', 256);
    if(fl->using_G)
        mx_add_color(node->d_name, MX_PINK);
    else
        mx_printstr(node->d_name); 
    mx_printstr(" -> ");
    readlink(node->path, buf, 256);
    mx_printstr(buf);
    return res;
}
