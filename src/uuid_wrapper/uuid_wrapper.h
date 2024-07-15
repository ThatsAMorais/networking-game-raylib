#ifndef UUID_WRAPPER_H
#define UUID_WRAPPER_H

#ifdef _WIN32
#include <windows.h>
#include <rpc.h>
#pragma comment(lib, "Rpcrt4.lib")
#elif __linux__ || __APPLE__
#include <uuid/uuid.h>
#else
#error "Platform not supported"
#endif

void generate_uuid(char* uuid_str);

#endif // UUID_WRAPPER_H
