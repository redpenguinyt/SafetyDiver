//
//  draw.h
//

#ifndef draw_h
#define draw_h

#include "physics.h"

#define TARGET_EXTENSION 1
#include "pd_api.h"

void drawWater(float offsetY);
void drawPlayer(Player player, float degrees, float rudderStrength, int heldScore);
void drawHUD(Player player, int score);

#endif /* draw_h */
