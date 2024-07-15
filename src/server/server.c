#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "game_logic.h"
#include "networking.h" // Add this line

// Function prototypes for handlePlayerJoin and handlePlayerLeave
void handlePlayerJoin(Peer peer, const char* data);
void handlePlayerLeave(Peer peer, const char* data);

void runServer(int port) {
    Client server;
    Peer peer;
    if (!initializeNetworking(&server, &peer, NULL, port)) {
        fprintf(stderr, "An error occurred while initializing the server.\n");
        return;
    }

    printf("Server started on port %d\n", port);

    GameState gameState;
    initGameState(&gameState);

    while (1) {
        const char* received_data = receiveMessage(server);
        if (received_data) {
            Message* msg = (Message*)received_data;
            switch (msg->type) {
                case MSG_TYPE_JOIN:
                    handlePlayerJoin(peer, msg->data);
                    break;
                case MSG_TYPE_LEAVE:
                    handlePlayerLeave(peer, msg->data);
                    break;
                default:
                    processPacket(&gameState, (void*)msg, sizeof(Message));
                    break;
            }
        }
    }

    cleanupNetworking(server, peer);
    printf("Server stopped.\n");
}

int main(int argc, char **argv) {
    int port = 0;

    if (loadConfig("config.ini", &port) != 0) {
        return 1;
    }

    if (argc > 1 && strcmp(argv[1], "runServer") == 0) {
        runServer(port);
        return 0;
    }

    printf("Usage: %s runServer\n", argv[0]);
    runServer(port);

    return 0;
}

// Implementations for handlePlayerJoin and handlePlayerLeave
void handlePlayerJoin(Peer peer, const char* data) {
    // Handle player join
    printf("Player joined: %s\n", data);
}

void handlePlayerLeave(Peer peer, const char* data) {
    // Handle player leave
    printf("Player left: %s\n", data);
}
