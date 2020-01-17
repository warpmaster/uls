#include "uls.h"

static void get_rc_num(int elements, int win_width, int col_width, 
t_table_info *table);

void mx_print_table(t_list_dir *head, t_flags *opts) {
    int col_width = 0;
    int elements = mx_list_size_dir(head, &col_width);
    t_table_info table;
    struct winsize w;
    const size_t static_win_size = 80;
    
    table.cols = elements;
    table.rows = 1;
    if (elements == 0)
        return;
    ioctl(0, TIOCGWINSZ, &w);
    
    col_width = (opts->using_G ? col_width + 1 
    : col_width + 8 - col_width % 8);

    get_rc_num(elements, (isatty(STDOUT_FILENO) ? w.ws_col : static_win_size),
    col_width, &table);
    mx_make_table(head, table, col_width, opts);
}

static void get_rc_num(int elements, int win_width, int col_width,
t_table_info *table) {
    int tot_width = elements * col_width;

    if (col_width < win_width) {
        while (tot_width > win_width) {
            table->cols = 0;
            table->rows++;
            for (int i = 0; i < elements; i++) {
                if (i % table->rows == 0)
                    table->cols++;
            }
            tot_width = table->cols * col_width;
        }
    }
    else {
        table->cols = 1;
        table->rows = elements;
    }
}
