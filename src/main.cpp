#include <cmath>
#include "raylib.h"
#include "raymath.h"

#include "gamecamera.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1440;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");


    float angle = 0.0f; // Initialize angle
    float radius = 20.0f; // Distance from the origin

    Vector3 playerPos = { 0.5f, 0.5f, 0.5f };
    Vector3 playerRot = { 0.0f, 0.0f, 0.0f };

	GameCamera gameCamera;

    auto playerMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    auto playerModel = LoadModelFromMesh(playerMesh);

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

		gameCamera.Update(GetMouseWheelMove(), GetMouseDelta());
		
        if (IsKeyPressed('Z'))
        {
            playerPos = (Vector3){ 0.5f, 0.5f, 0.5f };
			playerRot = (Vector3){ 0.0f, 0.0f, 0.0f };
			// gameCamera.Reset();
        }
        if (IsKeyDown('W'))
        {
            playerRot.z += 0.1745f;
        }
        if (IsKeyDown('S'))
        {
            playerRot.z -= 0.1745f;
        }
        if (IsKeyDown('A'))
        {
            playerRot.x += 0.1745f;
        }
        if (IsKeyDown('D'))
        {
            playerRot.x -= 0.1745f;
        }
		if (IsKeyDown('Q'))
        {
            playerRot.y += 0.1745f;
        }
        if (IsKeyDown('E'))
        {
            playerRot.y -= 0.1745f;
        }

        playerModel.transform = MatrixRotateXYZ(playerRot);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode3D(gameCamera.Get());

                DrawModel(playerModel, playerPos, 1.0f, RED);
				DrawModelWires(playerModel, playerPos, 1.0f, BLACK);
                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);
            DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(600, 5, 195, 100, BLUE);

            DrawText("Camera status:", 610, 15, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", gameCamera.Get().position.x, gameCamera.Get().position.y, gameCamera.Get().position.z), 610, 30, 10, BLACK);
            DrawText(TextFormat("- Field of view: (%06.3f)", gameCamera.Get().fovy), 610, 45, 10, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}