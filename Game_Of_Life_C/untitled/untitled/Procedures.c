#include <stdio.h>
#include <stdlib.h>
#include "Procedures.h"

char which_group(int y, int x, struct Cell *matrix, int nr_of_rows) {
    // Check if the row and column indices are within bounds
    if (y < 0 || y >= nr_of_rows || x < 0 || x >= nr_of_rows) {
        // Return 'X' if the indices are out of bounds
        return 'X';
    }
    int A = 0;
    int B = 0;
    for (int a = (y - 1); a < (y + 2); a++) {
        for (int b = (x - 1); b < (x + 2); b++) {
            // Only check cells if the indices are within bounds
            if (a >= 0 && a < nr_of_rows && b >= 0 && b < nr_of_rows) {
                if (matrix[nr_of_rows * a + b].Group == 'A' || matrix[nr_of_rows * a + b].Group == 'a')
                    A++;
                else if (matrix[nr_of_rows * a + b].Group == 'B' || matrix[nr_of_rows * a + b].Group == 'b')
                    B++;
            }
        }
    }
    if (A < B)
        return 'B';
    else return 'A';
}

int count_alive_neighbours(int y, int x, struct Cell *matrix, int nr_of_rows, int nr_of_cols) {
    int result = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            // Check if the current cell is within the bounds of the matrix
            if (i >= 0 && i < nr_of_rows && j >= 0 && j < nr_of_cols) {
                    result += matrix[i * nr_of_rows + j].State;
            }
        }
    }
    //This makes it so that it doesn't count itself as a neighbour
    return result - matrix[y * nr_of_rows + x].State;
}

//Updates to next generation
void next_generation(int nr_rows, int nr_col, struct Cell *Matrix, struct Cell *Canvas) {
    for (int y = 0; y < nr_rows; y++) {
        for (int x = 0; x < nr_col; x++) {
            int alive_neighbours = count_alive_neighbours(y, x, Canvas, nr_rows, nr_col);
            char A_or_B = which_group(y, x, Canvas, nr_rows);
            if (A_or_B == 'X') {
                Matrix[nr_rows * y + x].State = 0;
                Matrix[nr_rows * y + x].Group = 'x';
            }
            if (alive_neighbours == 3 && Canvas[nr_rows * y + x].State == 0) {
                Matrix[nr_rows * y + x].State = 1;
                if (A_or_B == 'A') {
                    Matrix[nr_rows * y + x].Group = 'A';
                } else { Matrix[nr_rows * y + x].Group = 'B'; }
            } else if (alive_neighbours < 2 && Canvas[nr_rows * y + x].State == 1) {
                Matrix[nr_rows * y + x].State = 0;
                Matrix[nr_rows * y + x].Group = 'x';
            } else if (Canvas[nr_rows * y + x].State == 1 && (alive_neighbours == 2 || alive_neighbours == 3)) {
                Matrix[nr_rows * y + x].State = 1;
                Matrix[nr_rows * y + x].Group = Canvas[nr_rows * y + x].Group;
            } else if (alive_neighbours > 3 && Canvas[nr_rows * y + x].State == 1) {
                Matrix[nr_rows * y + x].State = 0;
                Matrix[nr_rows * y + x].Group = 'x';
            } else {
                Matrix[nr_rows * y + x].State = 0;
                Matrix[nr_rows * y + x].Group = 'x';
            }
        }
    }
}

void Set_Matrix_in_Canvas(struct Cell *Matrix, struct Cell *Canvas, int nr_rows, int nr_col) {
    for (int y = 0; y < nr_rows; y++) {
        for (int x = 0; x < nr_col; x++) {
            // Use a pointer to access the cell in the Matrix and Canvas matrices
            struct Cell *cell_in_matrix = &Matrix[nr_rows * y + x];
            struct Cell *cell_in_canvas = &Canvas[nr_rows * y + x];
            // Copy the values from the cell in the Matrix to the cell in the Canvas
            cell_in_canvas->State = cell_in_matrix->State;
            cell_in_canvas->Group = cell_in_matrix->Group;
        }
    }
}

//Save generation to text file
void save_to_file(int nr_rows, int nr_col, struct Cell *Canvas, FILE *fp) {
    for (int a = 0; a < nr_rows; a++) {
        for (int b = 0; b < nr_col; b++) {
            fprintf(fp, "%c ", Canvas[a * nr_rows + b].Group);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
}

void initialize_row_col(int *nr_rows, int *nr_col, FILE *fp) {
    if (fp == NULL) {
        printf("Error: no fill exist");
        printf("\n");
    }
    fscanf(fp, "%i %i", nr_rows, nr_col);
}

void initialize_matrix(int nr_rows, int nr_col, struct Cell *Canvas, int bool, FILE *fp) {
    char Copy;
    if (bool == 1) {
        for (int y = 0; y < nr_rows; y++) {
            for (int x = 0; x < nr_col; x++) {
                fscanf(fp, "%c", &Copy);
                if (Copy == 'X' || Copy == 'x') {
                    Canvas[y * nr_rows + x].State = 0;
                    Canvas[y * nr_rows + x].Group = 'x';
                } else if (Copy == 'A' || Copy == 'a') {
                    Canvas[y * nr_rows + x].Group = 'A';
                    Canvas[y * nr_rows + x].State = 1;
                } else if (Copy == 'B' || Copy == 'b') {
                    Canvas[y * nr_rows + x].Group = 'B';
                    Canvas[y * nr_rows + x].State = 1;
                } else x = x - 1;
            }
        }
    } else {
        // if the matrix had no starting canvas this will make a random starting canvas
        for (int y = 0; y < nr_rows; y++) {
            for (int x = 0; x < nr_col; x++) {
                int state = rand() % 2; // generate a random number between 0 and 1
                Canvas[y * nr_rows + x].State = state;
                if (state == 0) {
                    Canvas[y * nr_rows + x].Group = 'X';
                } else {
                    int group = rand() % 2; // generate another random number between 0 and 1
                    if (group == 0) {
                        Canvas[y * nr_rows + x].Group = 'A';
                    } else {
                        Canvas[y * nr_rows + x].Group = 'B';
                    }
                }
            }
        }
    }
}