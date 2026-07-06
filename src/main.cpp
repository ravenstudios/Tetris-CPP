#include "raylib.h"
#include "Game.h"



int main(){
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Tetris");
    SetWindowFocused();
    while (!WindowShouldClose()){
        if (IsKeyPressed(KEY_Q)){
            CloseWindow();
            return 0;
        }
        
        BeginDrawing();

        ClearBackground(BLACK);

        // DrawText("Hello World!", 100, 100, 30, WHITE);
        game.Update();
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}