#include "uls.h"

static void init_opts(t_flags *opts);
static void check_arg(int argc, char *argv[], int i, int *is_error);
static int read_arg(int argc, char *argv[], t_flags *fl);
static void create_lists(char *argv, t_list_dir **f_list, t_list_dir **d_list, t_flags *fl);

int main(int argc, char **argv) {
    t_flags flag;
    int first_file_pos = 1;
    int is_error = 0;
    t_list_dir *file_list = NULL;
    t_list_dir *dir_list = NULL;

    init_opts(&flag);
    first_file_pos = read_arg(argc, argv, &flag);
    check_arg(argc, argv, first_file_pos, &is_error);
    if (first_file_pos == argc) {
        directory_walker(".", &flag, false);
        //system("leaks uls");
        return is_error;
    }
    for (int i = first_file_pos; i < argc; i++)
        create_lists(argv[i], &file_list, &dir_list, &flag);
    file_list = mx_sort_list_dir(file_list, &flag);
    dir_list = mx_sort_list_dir(dir_list, &flag);
    mx_constructor(file_list, dir_list, flag, argc - first_file_pos);
    //system("leaks uls");
    return is_error;
}

static void create_lists(char *argv, t_list_dir **f_list, t_list_dir **d_list, t_flags *fl){
    struct stat statbuf;

    if (lstat(argv, &statbuf) != -1) {
        if (mx_get_file_type(statbuf.st_mode) == 'd'
        || (mx_get_file_type(statbuf.st_mode) == 'l' && !fl->using_l))
            mx_push_front_dir(d_list, argv, NULL);
        else 
            mx_push_back_dir(f_list, argv, NULL);
    }
}

static void init_opts(t_flags *opts) {
    opts->using_l = false;
    opts->using_C = true;
    opts->using_1 = false;
    opts->using_a = false;
    opts->using_A = false;
    opts->using_G = false;
    opts->using_r = false;
    opts->using_R = false;
    opts->using_T = false;
    opts->using_n = false;
    opts->using_g = false;
    opts->using_u = false;
    opts->using_c = false;
    opts->using_S = false;
    opts->using_t = false;
}

static void check_arg(int argc, char *argv[], int i, int *is_error) {
    struct stat sb;
    t_list *bad_list = NULL;

    for(; i < argc; i++) {
        if(lstat(argv[i],  &sb) == -1) {
            *is_error = 1;
            mx_push_front(&bad_list, argv[i]);
        }
    }
    bad_list = mx_sort_list(bad_list, cmp);
    mx_print_bad_list(bad_list);
    mx_delete_list(&bad_list);
}


static int read_arg(int argc, char *argv[], t_flags *fl) {
    int pos = 1;
    
    if(!isatty(1)) {
        fl->using_C = false;
        fl->using_1 = true;
        //printf("debug_switch_1C\n");
    }
    for(int k = 1; k < argc; k++){
        if(*argv[k] == '-' && mx_strlen(argv[k]) != 1){
            pos++;
            fl = mx_get_flags(fl, argv[k]);
        }
    }
    return pos;
}
