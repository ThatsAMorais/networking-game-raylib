#include "ini.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int handler(void* user, const char* section, const char* name, const char* value) {
    int* port = (int*)user;

    if (strcmp(section, "network") == 0 && strcmp(name, "port") == 0) {
        *port = atoi(value);
    }

    return 1;
}

int loadConfig(const char* filename, int* port) {
    if (ini_parse(filename, handler, port) < 0) {
        printf("Can't load '%s'\n", filename);
        return 1;
    }

    if (*port == 0) {
        printf("No port specified in '%s'\n", filename);
        return 1;
    }

    return 0;
}
