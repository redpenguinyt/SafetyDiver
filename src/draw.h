//
//  draw.h
//

#ifndef draw_h
#define draw_h

#include "physics.h"

#define TARGET_EXTENSION 1
#include "pd_api.h"

void setupDraw(PlaydateAPI *p);

void drawWater(Player player);
void drawPlayer(Player player, float degrees, float rudderStrength);

#endif /* draw_h */
