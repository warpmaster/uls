#include "uls.h"

void mx_print_flag_1(t_list_dir *head, t_flags *opts) {
    if (!head || !opts) 
    	return;
    for (t_list_dir *w = head; w != NULL; w = w->next) {
        opts->using_G ? 
        mx_print_G_flag(w->d_name, w->statbuf->st_mode) :
        mx_printstr(w->d_name);
        mx_printchar('\n');
    }
}
