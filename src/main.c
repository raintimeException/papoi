#include "../include/raylib.h"

#define TITLE "papoi"
#define FPS 60

int main(void) {
    SetTraceLogLevel(LOG_ALL);

    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, TITLE);
    {
        // Load resources / Initialize variables at this point
    }
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        {
            // Update variables / Implement example logic at this
            // point
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);
        }
        EndDrawing();
    }

    // TODO: Unload all loaded resources at this point

    CloseWindow();
    return 0;
}
