//
//  hazards.c
//

#include "hazards.h"

#include "utils/rensutils.h"

static Hazard hazards[24];

void randomiseHazard(Hazard *hazard) {
	hazard->pos.x = rand() % 400;
	hazard->pos.y = WATER_LEVEL + rand() % (FLOOR_LEVEL - WATER_LEVEL);
	hazard->width = rand() % 100 + 20;
	hazard->height = rand() % 60 + 10;
}

bool isPosInHazard(Vec2F pos, Hazard hazard) {
	return pos.x >= hazard.pos.x && pos.x < (hazard.pos.x + hazard.width) && pos.y >= hazard.pos.y &&
		   pos.y < (hazard.pos.y + hazard.height);
}

// Public

void generateHazards(void) {
	for (size_t i = 0; i < (sizeof(hazards) / sizeof(Hazard)); i++) {
		randomiseHazard(&hazards[i]);
	}
}

bool processHazards(Player player) {
	for (size_t i = 0; i < (sizeof(hazards) / sizeof(Hazard)); i++) {
		if (isPosInHazard(player.pos, hazards[i])) {
			return true;
		}
	}

	return false;
}

void drawHazards(PlaydateAPI *pd, int offsetY) {
	for (size_t i = 0; i < (sizeof(hazards) / sizeof(Hazard)); i++) {
		pd->graphics->drawRect(hazards[i].pos.x, hazards[i].pos.y - offsetY, hazards[i].width, hazards[i].height, 0);
	}
}