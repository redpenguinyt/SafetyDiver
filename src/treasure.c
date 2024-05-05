//
//  treasure.c
//

#include "treasure.h"

#include "utils/rensutils.h"

static GoldPiece gold[64];

void randomiseGold(GoldPiece *goldPiece) {
	goldPiece->pos.x = rand() % 400;
	goldPiece->pos.y = rand() % 2000 + WATER_LEVEL;
	goldPiece->radius = rand() % 10 + 5;
	goldPiece->t = rand() % 6;
}

// Public

void generateGold(void) {
	for (size_t i = 0; i < (sizeof(gold) / sizeof(GoldPiece)); i++) {
		randomiseGold(&gold[i]);
	}
}

void processGold(Player player, int *score) {
	for (size_t i = 0; i < (sizeof(gold) / sizeof(GoldPiece)); i++) {
		Vec2F distanceVector;
		distanceVector.x = player.pos.x - gold[i].pos.x;
		distanceVector.y = player.pos.y - gold[i].pos.y;

		float distance = sqrtf(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
		if (distance < player.radius + gold[i].radius) {
			*score += 1;
			randomiseGold(&gold[i]);
		}
	}
}

void drawGold(PlaydateAPI *pd, int offsetY) {
	for (size_t i = 0; i < (sizeof(gold) / sizeof(GoldPiece)); i++) {
		gold[i].t += 0.05f;

		// Coin spin effect
		float xRadius = ceilf(gold[i].radius * (cosf(gold[i].t) / 2.0f + 0.5f));

		pd->graphics->drawEllipse(gold[i].pos.x - xRadius, gold[i].pos.y - gold[i].radius - offsetY + 140, xRadius * 2,
								  gold[i].radius * 2, 3, 0, 0, (LCDColor)0);
	}
}