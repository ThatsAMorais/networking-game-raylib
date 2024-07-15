#ifndef NETWORKING_H
#define NETWORKING_H

#include <stdbool.h>

typedef enum {
    MSG_TYPE_JOIN,
    MSG_TYPE_LEAVE,
    MSG_TYPE_STATE_UPDATE,
    MSG_TYPE_TEST
} MessageType;

typedef struct {
    MessageType type;
    char data[256];
} Message;

typedef void* Client;
typedef void* Peer;

bool initializeNetworking(Client* client, Peer* peer, const char* address, unsigned short port);
void cleanupNetworking(Client client, Peer peer);
void sendMessage(Peer peer, MessageType type, const char* data);
const char* receiveMessage(Client client);

#endif // NETWORKING_H
