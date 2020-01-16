#ifndef ULS_H
#define ULS_H

#define MINORBITS       24
#define MINORMASK       ((1U << MINORBITS) - 1)
#define MAJOR(dev)      ((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev)      ((unsigned int) ((dev) & MINORMASK))

#define RED  "\33[31m"
#define YELLOW  "\33[33m"
#define PINK  "\33[35m"
#define AQUA  "\33[36m"
#define BLUE  "\33[34m"
#define GREEN "\33[32m"
#define YELLOW_BLUE  "\33[43m\33[34m"
#define AQUA_BLUE  "\33[46m\33[34m"
#define GREEN_BLACK "\33[42m\33[30m"
#define BLACK_RED "\33[30m\33[41m"
#define AQUA_BLACK "\33[46m\33[30m"
#define YELLOW_BLACK "\33[43m\33[30m"
#define DEFAULT  "\33[0m"

#include "./libmx/inc/libmx.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <sys/errno.h>

typedef struct s_list_dir {
    char *d_name;
    char *path;
    struct stat *statbuf;
    struct s_list_dir *next;
} t_list_dir;

typedef struct s_flags {
    bool using_l;
    bool using_C;
    bool using_1;
    bool using_a;
    bool using_A;
    bool using_G;
    bool using_r;
    bool using_R;
    bool using_T;
    bool using_n;
    bool using_g;
    bool using_u;
    bool using_c;
    bool using_S;
    bool using_t;
}t_flags;

typedef struct s_column_size {
    int block1_msize;
    int block2_msize;
    int block3_msize;
    int block4_msize;
    int total_size; 
    struct passwd *pw;
    struct group *gr;
    int cur_block1_size;
    int cur_block2_size;
    int cur_block3_size;
    int cur_block4_size;
}t_col_size;

typedef struct s_node {
    t_list_dir *ptr;
}t_node;

typedef struct s_table {
    int cols;
    int rows;
}t_table_info;

typedef void (*fptr)(t_list_dir *first, t_list_dir *second, 
t_flags *opts);

t_list_dir *mx_create_node_dir(const char *d_name, const char *path);
void mx_push_front_dir(t_list_dir **list, const char *d_name, 
const char *path);
void mx_push_back_dir(t_list_dir **list, const char *d_name, const char *path);
int mx_list_size_dir(t_list_dir *list, int *max_len);
void mx_delete_list_dir(t_list_dir **head);
t_list_dir *mx_sort_list_dir(t_list_dir *lst, t_flags *opts);
char mx_get_file_type(mode_t value);
void mx_print_table(t_list_dir *head, t_flags *opts);
void mx_print_l_flag(t_list_dir *lst, t_flags *fl, bool pr_total);
void add_color(char *name, char *col);
void mx_print_G_flag(char *name, mode_t value);
void mx_print_flag_1(t_list_dir *head, t_flags *opts);
/*void */int mx_constructor(t_list_dir *file_list, t_list_dir *dir_list, t_flags flag,
int files_cnt);
void directory_walker(char *path, t_flags *opts, bool print_header, int *is_err);
t_list_dir *make_dir_list(char *path, t_list_dir *list,
t_flags *opts, int *error_no);
void print_dir_list(char *dir_name, t_list_dir *list, 
t_flags *opts, bool print_header);
t_flags *mx_get_flags(t_flags *fl, char *flags);
void cmp_lex_desc(t_list_dir *first, t_list_dir *second, 
t_flags *opts);
void cmp_size_desc(t_list_dir *first, t_list_dir *second, 
t_flags *opts);
void cmp_t_mod_desc(t_list_dir *first, t_list_dir *second, 
t_flags *opts);
void cmp_lex_asc(t_list_dir *first, t_list_dir *second, 
t_flags *opts);
void cmp_size_asc(t_list_dir *first, t_list_dir *second, 
t_flags *opts);
void cmp_t_mod_asc(t_list_dir *first, t_list_dir *second, 
t_flags *opts);
void swap(t_list_dir *first, t_list_dir *second);
//time_t get_time_type(t_list_dir *node, t_flags *opts);
struct timespec get_time_type(t_list_dir *node, t_flags *opts);
int mx_get_digits(int num);
void mx_print_perm_and_link(t_list_dir *w, t_col_size info);
void mx_print_size_and_time(t_list_dir *w, t_flags *fl, t_col_size info);
void mx_print_uid_gid(t_list_dir *w, t_flags *fl, t_col_size info);
void mx_print_name_or_link(t_list_dir *w, t_flags *fl);
void err_dir(char *path, int *error_no);
void mx_print_bad_list(t_list *lst);
bool cmp(void *s1, void *s2);

#endif
