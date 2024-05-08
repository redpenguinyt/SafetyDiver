//
//  player.h
//

#ifndef player_h
#define player_h

#include "physics.h"

#define TARGET_EXTENSION 1
#include "pd_api.h"

Player newPlayer(void);
/// Returns the rudder strength
float playerMovement(Player *player, float deltaTime);
void playerSounds(Player player);

#endif /* player_h */
