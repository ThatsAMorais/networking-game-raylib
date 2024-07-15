#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <enet/enet.h>
#include "config.h"
#include "game_logic.h"

void runServer(int port) {
    if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        exit(EXIT_FAILURE);
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    ENetHost *server;
    ENetEvent event;

    address.host = ENET_HOST_ANY;
    address.port = port;

    server = enet_host_create(&address, 32, 2, 0, 0);
    if (server == NULL) {
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", port);

    GameState gameState;
    initGameState(&gameState);

    while (1) {
        while (enet_host_service(server, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    printf("A packet of length %zu containing %s was received from %x:%u.\n",
                           event.packet->dataLength,
                           event.packet->data,
                           event.peer->address.host,
                           event.peer->address.port);
                    processPacket(&gameState, event.packet->data, event.packet->dataLength);
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("%x:%u disconnected.\n", event.peer->address.host, event.peer->address.port);
                    break;
                default:
                    printf("Unknown event type: %d\n", event.type);
                    break;
            }
        }
    }

    enet_host_destroy(server);
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
