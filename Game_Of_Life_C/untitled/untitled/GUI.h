#ifndef GUI_H_
#define GUI_H_

#include <stdio.h>
#include <stdlib.h>
#include "Procedures.h"

#include <SDL2/SDL.h>

#ifdef __MAC_10_15
	#define DPI_SCALING 2
#else
	#define DPI_SCALING 1
#endif

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
#define MEMORY 1000
//this is to ensure that we avoid memory leaks

extern int should_continue;
void initialize_window(const char *title);
void draw_window(int nr_rows, int  nr_cols ,struct Cell *Canvas);
void read_input();
void free_gui();

#endif /* GUI_H_ */
