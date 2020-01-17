#include "uls.h"

void mx_print_uid_gid(t_list_dir *w, t_flags *fl, t_col_size info) {
    char *uid = mx_itoa(w->statbuf->st_uid);

    if(!fl->using_g) {
        fl->using_n ? mx_printstr(uid) 
        : mx_printstr(info.pw->pw_name);
        for (int i = info.block2_msize - (fl->using_n 
        ? mx_get_digits(w->statbuf->st_uid)
        : mx_strlen(info.pw->pw_name)); i >= 0; i--)
            mx_printchar(' '); 
    }
    (!fl->using_n && info.gr != NULL) ? mx_printstr(info.gr->gr_name)
    : mx_printint(w->statbuf->st_gid);
    for (int i = info.block3_msize - ((!fl->using_n && info.gr != NULL)
    ? mx_strlen(info.gr->gr_name) 
    : mx_get_digits(w->statbuf->st_gid)); i >= 0; i--)
            mx_printchar(' ');
    if (malloc_size(uid) > 0)
        mx_strdel(&uid);
}
