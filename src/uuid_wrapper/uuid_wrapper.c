#include "uuid_wrapper.h"
#include <stdio.h>
#include <string.h>

void generate_uuid(char* uuid_str) {
#ifdef _WIN32
    UUID uuid;
    UuidCreate(&uuid);
    RPC_CSTR szUuid = NULL;
    UuidToStringA(&uuid, &szUuid);
    strcpy_s(uuid_str, 37, (char*)szUuid);
    RpcStringFreeA(&szUuid);
#elif __linux__ || __APPLE__
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_unparse(uuid, uuid_str);
#endif
}
