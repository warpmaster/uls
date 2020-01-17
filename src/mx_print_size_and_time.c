#include "uls.h"

static char *short_time(time_t *t, t_flags *fl);
static char *hex_minor (dev_t dev);
static char *major_minor (dev_t dev);
static char *get_time(t_list_dir *w, t_flags *fl);

void mx_print_size_and_time(t_list_dir *w, t_flags *fl, t_col_size info) {
    char *time_form = get_time(w, fl);

    if (mx_get_file_type(w->statbuf->st_mode) == 'c' 
        || mx_get_file_type(w->statbuf->st_mode) == 'b') {
        char *temp = major_minor(w->statbuf->st_rdev);

        mx_printstr(temp);
        mx_printchar(' ');
        free(temp);
    } 
    else {
        for (int i = info.block4_msize - mx_get_digits(w->statbuf->st_size);
         i >= 0; i--)
            mx_printchar(' ');
        mx_printint(w->statbuf->st_size);
        mx_printchar(' ');
    }
    mx_printstr(time_form);
    mx_printchar(' ');
    free(time_form);
}

static char *get_time(t_list_dir *w, t_flags *fl) {
    if(fl->using_u)
        return short_time(&w->statbuf->st_atime, fl);
    else if(fl->using_c)
        return short_time(&w->statbuf->st_ctime, fl);
    else
        return short_time(&w->statbuf->st_mtime, fl);
}

static char *short_time(time_t *t, t_flags *fl) {
    char *s;

    if(fl->using_T){
        s = mx_strndup((ctime)(t) + 4, 20);
    }
    else {
        if ((time(0) - *t) < 15768000 && (time(0) - *t) >= 0)
            s = mx_strndup((ctime)(t) + 4, 12);
        else {
            s = mx_strndup((ctime)(t) + 4, 7);
            s = mx_strncat(s, ((ctime)(t) + 19), 5);
        }
    }
    return s;
}

static char *hex_minor(dev_t dev) {
    char *minor = NULL;
    char *temp = NULL;

    if (MX_MINOR(dev) > 255) {
        minor = mx_nbr_to_hex(dev & 0xffffff);
        temp = mx_strnew(10);
        mx_memset(temp, '0', 10);
        temp[1] = 'x';
        for (int i = 10 - mx_strlen(minor), j = 0; i < 10; i++, j++)
            temp[i] = minor[j];
        free(minor);
        minor = temp;
    } 
    else {
        minor = mx_itoa(MX_MINOR(dev));
    }
    return minor;
}

static char *major_minor(dev_t dev) {
    char *major = mx_itoa(MX_MAJOR(dev));
    char *minor = hex_minor(dev);
    int tot_len = (mx_strlen(minor) > 3 ? 16 : 9);
    char *joined_str = mx_strnew(tot_len);

    mx_memset(joined_str, ' ', tot_len);
    joined_str[4] = ',';
    for (int len = mx_strlen(major), i = 4 - len, j = 0; j < len; i++, j++)
        joined_str[i] = major[j];
    for (int len = mx_strlen(minor), i = tot_len - len, j = 0;
    j < len; i++, j++)
        joined_str[i] = minor[j];
    if (malloc_size(minor) > 0)
        mx_strdel(&minor);
    if (malloc_size(major) > 0)
        mx_strdel(&major);
    return joined_str;
}

