#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initGameState(GameState* state) {
    state->roundNumber = 0;
}

void processPacket(GameState* state, const char* data, size_t length) {
    // Process the packet and update game state
    printf("Processing packet: %s\n", data);
    // Example logic: increment round number on receiving a specific packet
    if (strcmp(data, "next_round") == 0) {
        state->roundNumber++;
        printf("Round number incremented to %d\n", state->roundNumber);
    }
}
