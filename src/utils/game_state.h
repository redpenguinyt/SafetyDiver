//
//  game_state.h
//

#ifndef game_state_h
#define game_state_h

typedef enum {
	kGameStatePlaying,
	kGameStateOver
} GameState;

extern GameState gameState;

#endif /* game_state_h */