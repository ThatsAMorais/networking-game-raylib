#include "networking.h"
#include "enet_wrapper.h"
#include <stdio.h>
#include <string.h>

#ifndef _countof
#define _countof(array) (sizeof(array) / sizeof(array[0]))
#endif

// Function to initialize networking
bool initializeNetworking(Client* client, Peer* peer, const char* address, unsigned short port) {
    if (!enet_wrapper_initialize()) {
        return false;
    }

    *client = enet_wrapper_create_client();
    if (*client == NULL) {
        return false;
    }

    *peer = enet_wrapper_connect(*client, address, port);
    if (*peer == NULL) {
        return false;
    }

    return true;
}

// Function to clean up networking
void cleanupNetworking(Client client, Peer peer) {
    enet_wrapper_disconnect(peer);
    enet_wrapper_destroy_client(client);
    enet_wrapper_deinitialize();
}

// Function to send a message
void sendMessage(Peer peer, MessageType type, const char* data) {
    char message[512];
    snprintf(message, sizeof(message), "%d:%s", type, data);
    enet_wrapper_send(peer, message);
}

// Function to receive a message
const char* receiveMessage(Client client) {
    const char* received_data = enet_wrapper_receive(client);
    if (received_data) {
        static Message message;
        sscanf_s(received_data, "%d:%256[^\n]", (int*)&message.type, message.data, (unsigned)_countof(message.data));
        return received_data;
    }
    return NULL;
}
