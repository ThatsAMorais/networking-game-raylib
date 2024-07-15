// enet_wrapper.c
#include "enet_wrapper.h"
#include <enet/enet.h>
#include <stdio.h>

bool enet_wrapper_initialize() {
    return enet_initialize() == 0;
}

void enet_wrapper_deinitialize() {
    enet_deinitialize();
}

void* enet_wrapper_create_client() {
    return enet_host_create(NULL, 1, 2, 0, 0);
}

void enet_wrapper_destroy_client(void* client) {
    enet_host_destroy((ENetHost*)client);
}

void* enet_wrapper_connect(void* client, const char* address, unsigned short port) {
    ENetAddress enet_address;
    enet_address_set_host(&enet_address, address);
    enet_address.port = port;

    return enet_host_connect((ENetHost*)client, &enet_address, 2, 0);
}

void enet_wrapper_disconnect(void* peer) {
    enet_peer_disconnect((ENetPeer*)peer, 0);
}

bool enet_wrapper_service(void* client, int timeout, bool* is_connected) {
    ENetEvent event;
    while (enet_host_service((ENetHost*)client, &event, timeout) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                *is_connected = true;
                return true;
            case ENET_EVENT_TYPE_DISCONNECT:
                *is_connected = false;
                return true;
            default:
                break;
        }
    }
    return false;
}
