//
//  draw.h
//

#ifndef draw_h
#define draw_h

#include "physics.h"

#define TARGET_EXTENSION 1
#include "pd_api.h"

void setupDraw(PlaydateAPI *p);

void drawWater(void);
void drawPlayer(Player player, float degrees);

#endif /* draw_h */
