#ifndef PLAYER_PROFILE_H
#define PLAYER_PROFILE_H

#include <stdbool.h>

typedef struct {
    char guid[37]; // GUID for the player
    char username[50]; // Player's username
} PlayerProfile;

bool loadPlayerProfile(const char* filename, PlayerProfile* profile);
bool savePlayerProfile(const char* filename, const PlayerProfile* profile);
void generateNewProfile(PlayerProfile* profile);

#endif // PLAYER_PROFILE_H
