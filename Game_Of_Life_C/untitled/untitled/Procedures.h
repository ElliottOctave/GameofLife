#ifndef UNTITLED_PROCEDURES_H
#define UNTITLED_PROCEDURES_H
struct Cell {
    int State;
    char Group;
};

int count_alive_neighbours(int y, int x, struct Cell *matrix, int nr_of_rows, int nr_of_cols);
char which_group(int y, int x, struct Cell *matrix, int nr_of_rows);
void save_to_file(int nr_row, int nr_col, struct Cell *Canvas, FILE *fp);
void next_generation(int nr_rows, int nr_col, struct Cell *matrix, struct Cell *Canvas);
void Set_Matrix_in_Canvas(struct Cell *Matrix, struct Cell *Canvas, int nr_rows, int nr_col);
void initialize_matrix(int row, int col, struct Cell *Canvas, int bool, FILE *fp);
void initialize_row_col(int *row, int *col, FILE *fp);

#endif //UNTITLED_PROCEDURES_H
