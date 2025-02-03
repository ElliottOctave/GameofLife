#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Procedures.h"
#include "GUI.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    int row;
    int col;
    int bool;
    char *file;

    if (((argc > 2) && (strcmp(argv[1], "-f") == 0))) {
        file = argv[2];
        fp = fopen(file, "r");
        initialize_row_col(&row, &col, fp);
        bool = 1;
    } else if (((argc == 5) && (strcmp(argv[1], "-w") == 0)) && (strcmp(argv[3], "-h") == 0)) {
        col = atoi(argv[2]);
        row = atoi(argv[4]);
        file = "Random-matrix.txt";
        bool = 0;
    } else if (((argc == 5) && (strcmp(argv[3], "-w") == 0)) && (strcmp(argv[1], "-h") == 0)) {
        col = atoi(argv[4]);
        row = atoi(argv[2]);
        file = "Random-matrix.txt";
        bool = 0;
    }

    // Define Canvas and Matrix here
    struct Cell *Canvas = malloc(MEMORY * sizeof(struct Cell));
    struct Cell *Matrix = malloc(MEMORY * sizeof(struct Cell));

    fp = fopen(file, "r");
    initialize_matrix(row, col, Canvas, bool, fp);
    fp = fopen(file, "w");
    fprintf(fp, "%d \n", col);
    fprintf(fp, "%d \n", row);

    initialize_window("Game of Life");

    //here is a while loop that will continue until the user exits the window
    while (should_continue) {
        draw_window(row, col, Canvas);
        save_to_file(row, col, Canvas, fp);
        next_generation(row, col, Matrix, Canvas);
        Set_Matrix_in_Canvas(Matrix, Canvas, row, col);
        read_input();
    }
    free(Matrix);
    free(Canvas);
    free_gui();
    fclose(fp);
}