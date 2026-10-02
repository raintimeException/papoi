#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#define TITLE "papoi"
#define FPS 60
#define INTRO_ANIMATION_TIME_FC 10

typedef enum {
    GS_INTRO = 0,
    GS_MENU,
    GS_GAME,
    GS_END,
} Game_Screen;

typedef struct {
    Game_Screen current_screen;
    Texture2D intro_texture;
} Game_Data;

void show_intro(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);
    DrawTexture(g->intro_texture,
                GetScreenWidth() / 2 - g->intro_texture.width / 2,
                GetScreenHeight() / 2 - g->intro_texture.height / 2, WHITE);
}

static void DrawTextCenter(const char *text, int x, int y, int fontSize,
                           Color color) {
    Vector2 size = MeasureTextEx(GetFontDefault(), text, (float)fontSize, 3);
    Vector2 pos = (Vector2){x - size.x / 2, y - size.y / 2};
    DrawTextEx(GetFontDefault(), text, pos, (float)fontSize, 3, color);
}

void show_menu(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);

    int menu_width = 100;
    int menu_height = 100;

    const char *menu_text = "Menu";
    float menu_spacing = 1.0;
    Color menu_tint = WHITE;
    int font_sz = 18;

    DrawTextCenter(menu_text, GetScreenWidth() / 2, GetScreenHeight() / 2,
                   font_sz, menu_tint);
    const int options_count = 2;
    const char *options[options_count] = {
        "enter",
        "exit",
    };

    int scrollIndex = 0;
    int active = -1;
    int focus = -1;
    int rect_width = GuiGetFont().baseSize * strlen(options[0]);
    int rect_height = GuiGetFont().baseSize * 3 * options_count;
    Rectangle bounds =
        (Rectangle){.x = GetScreenWidth() / 2 - rect_width / 2,
                    .y = GetScreenHeight() / 2 + rect_height / 10,
                    .width = rect_width,
                    .height = rect_height};
    GuiListViewEx(bounds, options, options_count, &scrollIndex, &active,
                  &focus);

    if (active >= 0) {
        active %= options_count;
        switch (active) {
        default:
            TraceLog(LOG_FATAL, "ERROR: unknown option %d!\n", active);
            break;
        case 0:
            g->current_screen = GS_GAME;
            break;
        case 1:
            g->current_screen = GS_END;
            break;
        }
    }
}

void show_game(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);

    char dir[255] = {0};
    strcpy((char *)dir, GetWorkingDirectory());

    FilePathList file_path_list = LoadDirectoryFilesEx(dir, "*.*", false);

    int list_scroll_index = 0;
    int list_item_active = -1;
    int list_item_focused = -1;

    // todo: i want the items to be a geometric figures, walk through file file
    // system and kill (delete) files.
    GuiSetStyle(DEFAULT, TEXT_SIZE, GuiGetFont().baseSize * 2);

    GuiListViewEx(
        (Rectangle){
            .x = 0,
            .y = 0,
            .width = (float)GetScreenWidth(),
            .height = (float)GetScreenHeight(),
        },
        file_path_list.paths, file_path_list.count, &list_scroll_index,
        &list_item_active, &list_item_focused);
    if (list_item_active > 0) {
        list_item_active %= file_path_list.count;
        TraceLog(LOG_INFO, "You just pressed: %s\n",
                 file_path_list.paths[list_item_focused]);
    }
}

void show_game_over(Game_Data *g) {
    TraceLog(LOG_INFO, "%s\n", __FUNCTION__);
    int font_sz = 18; // todo: refactor this
    Color tint = WHITE;
    DrawTextCenter("Game Over\nPress Esc -> Exit\nPress Enter -> Menu",
                   GetScreenWidth() / 2, GetScreenHeight() / 2, font_sz, tint);
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ALL);

    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, TITLE);

    // load
    Game_Screen current_screen = GS_INTRO;

    const char *intro_image_file_name = "../third/resources/_the_intro.png";
    Texture2D intro_texture = LoadTexture(intro_image_file_name);

    Game_Data g = {
        .current_screen = current_screen,
        .intro_texture = intro_texture,
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
            ClearBackground(BLACK);
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
        }
        EndDrawing();
    }

    // unload

    CloseWindow();
    return 0;
}
