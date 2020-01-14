#include "uls.h"

static void print_reg(char *name, mode_t value);
static void print_dir(char *name, mode_t value);

void add_color(char *name, char *col){
    mx_printstr(col);
    mx_printstr(name);
    mx_printstr(DEFAULT);
}

void mx_print_G_flag(char *name, mode_t value) {
    switch (mx_get_file_type(value)) {
        case 'p': add_color(name, YELLOW);
            break;
        case 'c': add_color(name, YELLOW_BLUE);
            break;
        case 'd': print_dir(name, value);
            break;
        case 'b': add_color(name, AQUA_BLUE);
            break;
        case '-': print_reg(name, value);
            break;
        case 'l': add_color(name, PINK);
            break;
        case 's': add_color(name, GREEN);
            break;
        default: mx_printstr(name);
    }
}

static void print_reg(char *name, mode_t value){
    if(((value & 0x040) && (value & 0x800)) 
    || (!(value & 0x040) && (value & 0x800)))
        add_color(name, BLACK_RED);
    else if(value & 0x040 && !(value & 0x800) 
    && (((value & 0x008) && (value & 0x400)) 
    || (!(value & 0x008) && (value & 0x400))))
        add_color(name, AQUA_BLACK);
    else if((value & 0x040 && !(value & 0x800)) 
    || (value & 0x008 && !(value & 0x400)) 
    || (value & 0x001 && !(value & 0x200)) 
    || (value & 0x001 && value & 0x200))
        add_color(name, RED);
    else 
        add_color(name, DEFAULT);
}

static void print_dir(char *name, mode_t value){
    if((value & 0x002) &&((value & 0x001 && value & 0x200) 
    || (value & 0x001 && value & 0x200)))
        add_color(name, GREEN_BLACK);
    else if(value & 0x002 && (value & 0x001 && !(value & 0x200)))
        add_color(name, YELLOW_BLACK);
    else
        add_color(name, BLUE);
}
