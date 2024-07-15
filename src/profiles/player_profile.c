#include "player_profile.h"
#include "uuid_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateNewProfile(PlayerProfile* profile) {
    generate_uuid(profile->guid);
    strcpy_s(profile->username, sizeof(profile->username), "Player");
}

bool loadPlayerProfile(const char* filename, PlayerProfile* profile) {
    FILE* file;
    fopen_s(&file, filename, "r");
    if (!file) return false;

    fscanf_s(file, "GUID: %36s\n", profile->guid, (unsigned)_countof(profile->guid));
    fscanf_s(file, "Username: %49s\n", profile->username, (unsigned)_countof(profile->username));

    fclose(file);
    return true;
}

bool savePlayerProfile(const char* filename, const PlayerProfile* profile) {
    FILE* file;
    fopen_s(&file, filename, "w");
    if (!file) return false;

    fprintf(file, "GUID: %s\n", profile->guid);
    fprintf(file, "Username: %s\n", profile->username);

    fclose(file);
    return true;
}
