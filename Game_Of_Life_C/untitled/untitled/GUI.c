#include "GUI.h"
#include "Procedures.h"

static SDL_Renderer *renderer;

static SDL_Window *window;

int mouse_x = 0;
int mouse_y = 0;

int should_continue = 1;

void initialize_window(const char *title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error while initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow(title, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        printf("Error: %s\n", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return (event->type == SDL_MOUSEBUTTONDOWN) ||
           (event->type == SDL_KEYDOWN) ||
           (event->type == SDL_QUIT);
}

void read_input() {
    SDL_Event event;
    while (!SDL_PollEvent(&event) || !is_relevant_event(&event)) {}
    switch (event.type) {
        case SDL_QUIT:
            should_continue = 0;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouse_x = event.button.x;
            mouse_y = event.button.y;
            break;
    }
}

void clear_window() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void draw_rectangle(int x, int y, int width, int height) {
    SDL_Rect rectangle = {x * DPI_SCALING, y * DPI_SCALING, width * DPI_SCALING, height * DPI_SCALING};
    SDL_RenderFillRect(renderer, &rectangle);
}

void draw_window(int nr_rows, int nr_cols, struct Cell *Canvas) {
    clear_window();
    for (int y = 0; y < nr_rows; y++) {
        for (int x = 0; x < nr_cols; x++) {
            char group = Canvas[nr_rows * y + x].Group;
            if ((group == 'A') || (group == 'a')) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            } else if ((group == 'B') || (group == 'b')) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            } else if ((group == 'X') || (group == 'x')) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            draw_rectangle(x * (WINDOW_WIDTH / nr_cols), y * (WINDOW_HEIGHT / nr_rows), WINDOW_WIDTH / nr_cols,
                           WINDOW_HEIGHT / nr_rows);
        }
    }
    SDL_RenderPresent(renderer);
}

void free_gui() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}