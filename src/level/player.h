//
//  player.h
//

#ifndef player_h
#define player_h

#include "physics.h"

Player newPlayer(void);
void playerMovement(Player *player, float deltaTime);
void playerSounds(Player player);

#endif /* player_h */
