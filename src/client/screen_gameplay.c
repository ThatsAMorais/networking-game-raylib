#include "raylib.h"
#include "screens.h"
#include "enet_wrapper.h"
#include <stdio.h>
#include <string.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    printf("Initializing Gameplay Screen...\n");
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    framesCounter++;

    // Send test packet every second
    if (framesCounter % 60 == 0)
    {
        const char* testMessage = "Test packet from client";
        printf("Sending test packet: %s\n", testMessage);
        enet_wrapper_send(peer, testMessage);
    }

    // Service the connection and process any received packets
    bool is_connected;
    enet_wrapper_service(client, 0, &is_connected);
    if (!is_connected) {
        printf("Lost connection to the server.\n");
        finishScreen = 1;  // Indicate we should exit the gameplay screen
        return;
    }

    const char* received_data = enet_wrapper_receive(client);
    if (received_data)
    {
        printf("Received: %s\n", received_data);
    }

    // Check if the user wants to end the game
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        printf("User requested to finish the game.\n");
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    printf("Unloading Gameplay Screen...\n");
    // Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
