//
//  hazards.h
//

#ifndef hazards_h
#define hazards_h

#include "physics.h"
#include <stdbool.h>

typedef struct {
	Vec2F pos;
	float width, height;
} Hazard;

void regenerateHazards(void);
/// Returns true if collided
bool processHazardCollisions(Player *player);
void drawHazards(int offsetY);

#endif /* hazards_h */
