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
// Connecting Screen Functions Definition
//----------------------------------------------------------------------------------

// Connecting Screen Initialization logic
void InitConnectingScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    countdown = 10;
    snprintf(connectionMessage, sizeof(connectionMessage), "Connecting to Server...");

    if (!enet_wrapper_initialize())
    {
        snprintf(connectionMessage, sizeof(connectionMessage), "Failed to initialize ENet");
        return;
    }

    client = enet_wrapper_create_client();

    if (client == NULL)
    {
        snprintf(connectionMessage, sizeof(connectionMessage), "Failed to create ENet client");
        return;
    }

    peer = enet_wrapper_connect(client, "127.0.0.1", 56841);

    if (peer == NULL)
    {
        snprintf(connectionMessage, sizeof(connectionMessage), "Failed to connect to server");
        return;
    }
}

// Connecting Screen Update logic
void UpdateConnectingScreen(void)
{
    bool service_result = enet_wrapper_service(client, 0, &isConnected);
    if (isConnected)
    {
        snprintf(connectionMessage, sizeof(connectionMessage), "Connected! Starting game in %d", countdown);
        framesCounter++;
        if (framesCounter >= 60)
        {
            framesCounter = 0;
            countdown--;
        }
        if (countdown <= 0)
        {
            finishScreen = 1;
        }
    }
    else
    {
        snprintf(connectionMessage, sizeof(connectionMessage), "Connecting to Server...");
    }
}

// Connecting Screen Draw logic
void DrawConnectingScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ORANGE);
    Vector2 pos = { 20, 20 };
    DrawTextEx(font, "CONNECTING SCREEN", pos, font.baseSize*3.0f, 4, DARKGRAY);
    DrawText(connectionMessage, 20, 80, 20, DARKGRAY);
}

// Connecting Screen Unload logic
void UnloadConnectingScreen(void)
{
    enet_wrapper_disconnect(peer);
    enet_wrapper_destroy_client(client);
    enet_wrapper_deinitialize();
}

// Connecting Screen should finish?
int FinishConnectingScreen(void)
{
    return finishScreen;
}
