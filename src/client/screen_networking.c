#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Networking Screen Functions Definition
//----------------------------------------------------------------------------------

// Networking Screen Initialization logic
void InitNetworkingScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
}

// Networking Screen Update logic
void UpdateNetworkingScreen(void)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
    }
}

// Networking Screen Draw logic
void DrawNetworkingScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    Vector2 pos = { 20, 20 };
    DrawTextEx(font, "NETWORKING SCREEN", pos, font.baseSize*3.0f, 4, DARKGRAY);
    DrawText("Press ENTER to Connect to Server", 20, 80, 20, DARKGRAY);
}

// Networking Screen Unload logic
void UnloadNetworkingScreen(void)
{
    // Unload networking screen variables here
}

// Networking Screen should finish?
int FinishNetworkingScreen(void)
{
    return finishScreen;
}
