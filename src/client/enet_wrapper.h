#ifndef ENET_WRAPPER_H
#define ENET_WRAPPER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations for ENet operations
bool enet_wrapper_initialize();
void enet_wrapper_deinitialize();
void* enet_wrapper_create_client();
void enet_wrapper_destroy_client(void* client);
void* enet_wrapper_connect(void* client, const char* address, unsigned short port);
void enet_wrapper_disconnect(void* peer);
bool enet_wrapper_service(void* client, int timeout, bool* is_connected);
void enet_wrapper_send(void* peer, const char* data);
const char* enet_wrapper_receive(void* client);

#ifdef __cplusplus
}
#endif

#endif // ENET_WRAPPER_H
