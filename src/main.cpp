#include <cmath>
#include "raylib.h"

#include "gamecamera.h"
#include "player.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1440;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Break-out");

    float angle = 0.0f; // Initialize angle
    float radius = 20.0f; // Distance from the origin

    GameCamera gameCamera;

    Player player;

    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
 
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        gameCamera.Update(GetMouseWheelMove(), GetMouseDelta());

        player.HandleKeyInput();
        player.Move(deltaTime);

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode3D(gameCamera.Get());

                DrawModel(player.GetModel(), player.GetPos(), 1.0f, RED);
                DrawModelWires(player.GetModel(), player.GetPos(), 1.0f, BLACK);
                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);
            DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(600, 5, 195, 100, BLUE);

            DrawText("Camera status:", 610, 15, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", gameCamera.Get().position.x, gameCamera.Get().position.y, gameCamera.Get().position.z), 610, 30, 10, BLACK);
            DrawText(TextFormat("- Field of view: (%06.3f)", gameCamera.Get().fovy), 610, 45, 10, BLACK);
            
            DrawText("Player status:", 610, 60, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", player.GetPos().x, player.GetPos().y, player.GetPos().z), 610, 75, 10, BLACK);
            DrawText(TextFormat("- Rotation: (%06.3f, %06.3f, %06.3f)", player.GetRot().x, player.GetRot().y, player.GetRot().z), 610, 90, 10, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}