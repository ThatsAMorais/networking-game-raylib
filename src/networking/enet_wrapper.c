#include "enet_wrapper.h"
#include <enet/enet.h>
#include <stdio.h>
#include <string.h>

bool enet_wrapper_initialize() {
    printf("Initializing ENet...\n");
    if (enet_initialize() != 0) {
        printf("Failed to initialize ENet.\n");
        return false;
    }
    printf("ENet initialized successfully.\n");
    return true;
}

void enet_wrapper_deinitialize() {
    printf("Deinitializing ENet...\n");
    enet_deinitialize();
    printf("ENet deinitialized.\n");
}

void* enet_wrapper_create_client() {
    printf("Creating ENet client...\n");
    ENetHost* client = enet_host_create(NULL, 1, 2, 0, 0);
    if (client == NULL) {
        printf("Failed to create ENet client.\n");
    } else {
        printf("ENet client created successfully.\n");
    }
    return client;
}

void enet_wrapper_destroy_client(void* client) {
    printf("Destroying ENet client...\n");
    enet_host_destroy((ENetHost*)client);
    printf("ENet client destroyed.\n");
}

void* enet_wrapper_connect(void* client, const char* address, unsigned short port) {
    printf("Connecting to server at %s:%u...\n", address, port);
    ENetAddress enet_address;
    enet_address_set_host(&enet_address, address);
    enet_address.port = port;

    ENetPeer* peer = enet_host_connect((ENetHost*)client, &enet_address, 2, 0);
    if (peer == NULL) {
        printf("Failed to connect to server.\n");
    } else {
        printf("Connected to server successfully.\n");
    }
    return peer;
}

void enet_wrapper_disconnect(void* peer) {
    printf("Disconnecting from server...\n");
    enet_peer_disconnect((ENetPeer*)peer, 0);
    printf("Disconnected from server.\n");
}

bool enet_wrapper_service(void* client, int timeout, bool* is_connected) {
    ENetEvent event;
    while (enet_host_service((ENetHost*)client, &event, timeout) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("Connection event received.\n");
                *is_connected = true;
                return true;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("Disconnection event received.\n");
                *is_connected = false;
                return true;
            default:
                break;
        }
    }
    return false;
}

void enet_wrapper_send(void* peer, const char* data) {
    printf("Sending data: %s\n", data);
    ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send((ENetPeer*)peer, 0, packet);
    enet_host_flush(((ENetPeer*)peer)->host);
    printf("Data sent.\n");
}

const char* enet_wrapper_receive(void* client) {
    static char received_data[1024];
    ENetEvent event;
    while (enet_host_service((ENetHost*)client, &event, 0) > 0) {
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            printf("Received data: %s\n", (char*)event.packet->data);
            strncpy_s(received_data, sizeof(received_data), (char*)event.packet->data, sizeof(received_data) - 1);
            received_data[sizeof(received_data) - 1] = '\0';
            enet_packet_destroy(event.packet);
            return received_data;
        }
    }
    return NULL;
}
