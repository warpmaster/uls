#include "uls.h"

static void check_output_flags(t_flags *opts, char *flags);
static void check_info_flag(t_flags *opts, char *flags);
static void check_l_miniflags(t_flags *opts, char *flags);
static void check_gn_flags(t_flags *opts, char *flags);

t_flags *mx_get_flags(t_flags *fl, char *flags) {
    if(*++flags == '\0') {
        exit(1);
    }
    if(mx_is_valid_flag(flags)) {
        check_output_flags(fl, flags);
        check_info_flag(fl, flags);
        check_l_miniflags(fl, flags);
        check_gn_flags(fl, flags);
        if(!isatty(STDOUT_FILENO))
            fl->using_G = false;
    }
    else {
        mx_printerr("usage: uls [-lC1aAGrRTngucSt] [file ...]\n");
        exit(1);
    }
    return fl;
}

static void check_output_flags(t_flags *opts, char *flags) {
    while(*flags) {
        switch (*flags) {
            case 'l': opts->using_l = true;
                opts->using_C = false;
                opts->using_1 = false;
                break;
            case 'C': opts->using_C = true;
                opts->using_l = false;
                opts->using_1 = false;
                break;
            case '1': opts->using_1 = true;
                opts->using_C = false;
                opts->using_l = false;
                break;
            case 'r': opts->using_r = true;
                break;
        }
        flags++;
    }
}

static void check_info_flag(t_flags *opts, char *flags) {
    while(*flags) {
        switch (*flags) {
            case 'a': opts->using_a = true;
                opts->using_A = false;
                break;
            case 'A':
                opts->using_A = !opts->using_a ? true : false;
                break;
            case 'G': opts->using_G = true;
                break;
            case 'R': opts->using_R = true;
                break;
            case 'S': opts->using_S = true;
                break;
            case 't':
                opts->using_t = !opts->using_S ? true : false;
        }
        flags++;
    }
}

static void check_l_miniflags(t_flags *opts, char *flags) {
    while(*flags) {
        switch (*flags) {
        case 'T': opts->using_T = true;
            break;
        case 'u': opts->using_u = true;
            opts->using_c = false;
            break;
        case 'c': opts->using_c = true;
            opts->using_u = false;
            break;
        }
        flags++;
    }
}

static void check_gn_flags(t_flags *opts, char *flags){
    while(*flags) {
        switch (*flags) {
            case 'n': opts->using_n = true;
            opts->using_l = true;
            opts->using_C = false;
            opts->using_1 = false;
            break;
        case 'g': opts->using_g = true;
            opts->using_l = true;
            opts->using_C = false;
            opts->using_1 = false;
            break;
        }
        flags++;
    }
}
