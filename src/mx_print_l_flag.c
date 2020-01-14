#include "uls.h"

static void init_cur_info(t_col_size *buf, t_list_dir *w, t_flags *fl);
static void init_start_info(t_col_size *buf);
static t_col_size get_column_size(t_list_dir *lst, t_flags *fl);

void mx_print_l_flag(t_list_dir *lst, t_flags *fl, bool pr_total) {
    t_col_size info = get_column_size(lst, fl);

    if (pr_total) {
        mx_printstr("total ");
        mx_printint(info.total_size);
        mx_printchar('\n');
    }
    for (t_list_dir *w = lst; w != NULL; w = w->next) {
        info.pw = getpwuid(w->statbuf->st_uid);
        info.gr = getgrgid(w->statbuf->st_gid);
        mx_print_perm_and_link(w, info);
        mx_print_uid_gid(w, fl, info);
        mx_print_size_and_time(w, fl, info);
        mx_print_name_or_link(w, fl);
    }
}

static void init_cur_info(t_col_size *buf, t_list_dir *w, t_flags *fl) {
    buf->cur_block1_size = 0;
    buf->cur_block2_size = 0;
    buf->cur_block3_size = 0;
    buf->cur_block4_size = 0;
    buf->cur_block1_size = mx_get_digits(w->statbuf->st_nlink);
    if(!fl->using_n)
        buf->cur_block2_size = (buf->pw != NULL 
        ? mx_strlen(buf->pw->pw_name) + 1 : 0);
    else
        buf->cur_block2_size = mx_get_digits(w->statbuf->st_uid) + 1;
    if(fl->using_n)
        buf->cur_block3_size = mx_get_digits(w->statbuf->st_gid);
    else            
        buf->cur_block3_size = (buf->gr != NULL ? mx_strlen(buf->gr->gr_name)
        : mx_get_digits(w->statbuf->st_gid));
    if (mx_get_file_type(w->statbuf->st_mode) == 'c' 
        || mx_get_file_type(w->statbuf->st_mode) == 'b')
        buf->cur_block4_size = 8;
    else
        buf->cur_block4_size = mx_get_digits(w->statbuf->st_size);
}

static void init_start_info(t_col_size *buf) {
    buf->block1_msize = 0;
    buf->block2_msize = 0;
    buf->block3_msize = 0;
    buf->block4_msize = 0;
    buf->total_size = 0; 
}

static t_col_size get_column_size(t_list_dir *lst, t_flags *fl) {
    t_col_size buf;

    init_start_info(&buf);
    for (t_list_dir *w = lst; w != NULL; w = w->next) {
        buf.pw = getpwuid(w->statbuf->st_uid);
        buf.gr = getgrgid(w->statbuf->st_gid);
        init_cur_info(&buf, w, fl);
        if (buf.cur_block1_size > buf.block1_msize)
            buf.block1_msize = buf.cur_block1_size;
        if (buf.cur_block2_size > buf.block2_msize)
            buf.block2_msize = buf.cur_block2_size;
        if (buf.cur_block3_size > buf.block3_msize)
            buf.block3_msize = buf.cur_block3_size;
        if (buf.cur_block4_size > buf.block4_msize)
            buf.block4_msize = buf.cur_block4_size;
        buf.total_size += w->statbuf->st_blocks;
    }
    return buf;
}
