//
//  treasure.h
//

#ifndef treasure_h
#define treasure_h

#include "physics.h"

typedef struct {
	Vec2F pos;
	float radius;
	float t;
} GoldPiece;

void regenerateGoldPositions(void);
void processGold(Player player, int *score);
void drawGold(int offsetY);

#endif /* treasure_h */
