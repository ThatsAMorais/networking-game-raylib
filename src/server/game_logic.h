#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

typedef struct {
    // Add your game state variables here
    int roundNumber;
} GameState;

void initGameState(GameState* state);
void processPacket(GameState* state, const char* data, size_t length);

#endif // GAME_LOGIC_H
