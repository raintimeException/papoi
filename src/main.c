#include "../include/raylib.h"

#define TITLE "papoi"
#define FPS 60
#define INTRO_ANIMATION_TIME_FC 120

typedef enum {
    GS_INTRO = 0,
    GS_MENU,
    GS_GAME,
    GS_END,
} Game_Screen;

typedef struct {
    Game_Screen current_screen;
} Game_Data;

void show_intro(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);
    // todo
}

void show_menu(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);
    // todo
}

void show_game(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);
    // todo
    static int frame_counter = 0;
    frame_counter++;
    if (frame_counter > 100) { // todo: deleteme
        g->current_screen = GS_END;
    }
}

void show_game_over(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);
    // todo
}

int main(void) {
    SetTraceLogLevel(LOG_ALL);

    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, TITLE);

    // load
    Game_Screen current_screen = GS_INTRO;
    Game_Data g = {
        .current_screen = current_screen,
        // add more
    };
    int frame_counter = 0;

    SetTargetFPS(FPS);
    while (!WindowShouldClose()) {
        {
            switch (g.current_screen) {
            case GS_INTRO: {
                frame_counter++;
                if (frame_counter > INTRO_ANIMATION_TIME_FC) {
                    g.current_screen = GS_MENU;
                }
            } break;
            case GS_MENU: {
                if (IsKeyPressed(KEY_ENTER)) {
                    g.current_screen = GS_GAME;
                }
            } break;
            case GS_GAME: {
                if (IsKeyPressed(KEY_ESCAPE)) {
                    g.current_screen = GS_MENU;
                }
            } break;
            case GS_END: {
                if (IsKeyPressed(KEY_ENTER)) {
                    g.current_screen = GS_MENU;
                }
            } break;
            default: {
                TraceLog(LOG_FATAL, "unknown current_screen");
                return -1;
            }
            }

            // update variables / implement example logic
        }

        BeginDrawing();
        {
            switch (g.current_screen) {
            case GS_INTRO: {
                show_intro(&g);
            } break;
            case GS_MENU: {
                show_menu(&g);
            } break;
            case GS_GAME: {
                show_game(&g);
            } break;
            case GS_END: {
                show_game_over(&g);
            } break;
            default: {
                TraceLog(LOG_FATAL, "unknown current_screen");
                return -1;
            }
            }
            ClearBackground(BLACK);
        }
        EndDrawing();
    }

    // unload

    CloseWindow();
    return 0;
}
