//
//  hazards.h
//

#ifndef hazards_h
#define hazards_h

#include "physics.h"
#include <stdbool.h>

#define TARGET_EXTENSION 1
#include "pd_api.h"

typedef struct {
	Vec2F pos;
	float width, height;
} Hazard;

void setupHazards(void);
/// Returns true if collided
bool processHazardCollisions(Player *player);
void drawHazards(int offsetY);

#endif /* hazards_h */
