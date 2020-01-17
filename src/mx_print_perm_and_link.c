#include "uls.h"

static void print_perm_type(mode_t value);
static char return_acl(char *filename);

void mx_print_perm_and_link(t_list_dir *w, t_col_size info) {
    mx_printchar(mx_get_file_type(w->statbuf->st_mode));
    print_perm_type(w->statbuf->st_mode);
    mx_printchar(return_acl(w->path));
    mx_printchar(' ');
    for (int i = info.block1_msize - mx_get_digits(w->statbuf->st_nlink);
    i > 0; i--)
        mx_printchar(' ');
    mx_printint(w->statbuf->st_nlink);
    mx_printchar(' ');
}

static void print_perm_type(mode_t value) {
    value & 0x100 ? mx_printchar('r') : mx_printchar('-');
    value & 0x080 ? mx_printchar('w') : mx_printchar('-');
    value & 0x040 ? (value & 0x800 ? mx_printchar('s') : mx_printchar('x')) 
    : (value & 0x800 ? mx_printchar('S') : mx_printchar('-'));
    value & 0x020 ? mx_printchar('r') : mx_printchar('-');
    value & 0x010 ? mx_printchar('w') : mx_printchar('-');
    value & 0x008 ? (value & 0x400 ? mx_printchar('s') : mx_printchar('x')) 
    : (value & 0x400 ? mx_printchar('S') : mx_printchar('-'));
    value & 0x004 ? mx_printchar('r') : mx_printchar('-');
    value & 0x002 ? mx_printchar('w') : mx_printchar('-');
    value & 0x001 ? (value & 0x200 ? mx_printchar('t') : mx_printchar('x')) 
    : (value & 0x200 ? mx_printchar('T') : mx_printchar('-'));
}

static char return_acl(char *filename) {
    acl_t acl = acl_get_file(filename, ACL_TYPE_EXTENDED);
    
    if (listxattr(filename, NULL, 0, XATTR_NOFOLLOW) > 0) {
        acl_free(acl);
        return '@';
    } 
    else if (acl == NULL) {
        acl_free(acl);
        return ' ';
    }
    else {
        acl_free(acl);
        return '+';
    }
}
