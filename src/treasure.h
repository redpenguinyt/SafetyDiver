//
//  treasure.h
//

#ifndef treasure_h
#define treasure_h

#include "physics.h"

#define TARGET_EXTENSION 1
#include "pd_api.h"

typedef struct {
	Vec2F pos;
	float radius;
	float t;
} GoldPiece;

void setupTreasure(PlaydateAPI *p);
void processGold(Player player, int *score);
void drawGold(int offsetY);

#endif /* treasure_h */
