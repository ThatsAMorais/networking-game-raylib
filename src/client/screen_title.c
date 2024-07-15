#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static const char* gameTitle = "Networking Game"; // Game title

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // Update TITLE screen variables here!

    // Press enter or tap to change to NETWORKING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // Draw TITLE screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);

    // Draw game title
    Vector2 titlePos = { (float)(GetScreenWidth() / 2 - (int)(MeasureTextEx(font, gameTitle, (float)(font.baseSize * 3.0f), 4).x / 2)), (float)(GetScreenHeight() / 3) };
    DrawTextEx(font, gameTitle, titlePos, (float)(font.baseSize * 3.0f), 4, DARKGREEN);

    // Draw instructions
    Vector2 instructionPos = { (float)(GetScreenWidth() / 2 - MeasureText("PRESS ENTER or TAP to BEGIN", 20) / 2), (float)(GetScreenHeight() * 2 / 3) };
    DrawText("PRESS ENTER or TAP to BEGIN", (int)instructionPos.x, (int)instructionPos.y, 20, DARKGREEN);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}
