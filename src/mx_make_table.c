#include "uls.h"

static t_node **create_table(int rows, int cols);
static void fill_table(t_list_dir *head, t_node **arr, int rows);
static void print_table(t_node **arr, t_table_info table, int col_width,
t_flags *opts);
static void delete_table(t_node ***arr, int rows);

void mx_make_table(t_list_dir *head, t_table_info table, int col_width,
t_flags *opts) {
    t_node **arr = create_table(table.rows, table.cols);

    if (!arr)
        return;
    fill_table(head, arr, table.rows);
    print_table(arr, table, col_width, opts);
    delete_table(&arr, table.rows);
}

static t_node **create_table(int rows, int cols) {
    t_node **arr;

    arr = (t_node **)malloc(rows * sizeof(t_node*));
    for (int i = 0; i < rows; i++)
        arr[i] = (t_node *)malloc(cols * sizeof(t_node *));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            arr[i][j].ptr = NULL;
    return arr;
}

static void fill_table(t_list_dir *head, t_node **arr, int rows) {
    int row = 0;
    int col = -1;

    for (t_list_dir *w = head; w != NULL; w = w->next) {
        if (row % rows == 0) {
            row = 0;
            col++;
        }
        arr[row][col].ptr = w;
        row++;
    }
}

static void print_table(t_node **arr, t_table_info table, int col_width,
t_flags *opts) {
    for (int i = 0; i < table.rows; i++) {
        for (int j = 0; j < table.cols; j++)
            if (arr[i][j].ptr != NULL) {
                opts->using_G ? 
                mx_print_G_flag(arr[i][j].ptr->d_name, 
                arr[i][j].ptr->statbuf->st_mode) : 
                mx_printstr(arr[i][j].ptr->d_name);
                if (j != table.cols - 1 
                && !(j == table.cols - 2 && arr[i][j+1].ptr == NULL)) {
                    int strlen = mx_strlen(arr[i][j].ptr->d_name);
                    int tabs = (col_width - strlen) / 8;

                    if (strlen % 8 != 0)
                        tabs++;
                    for (int i = 0; i < tabs; i++)
                        mx_printchar('\t');
                }
            }
        mx_printchar('\n');
    }
}

static void delete_table(t_node ***arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free((*arr)[i]);
    }
    free(*arr);
    *arr = NULL;
}
