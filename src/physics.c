//
//  physics.c
//

#include "physics.h"

#include "rensutils.h"

static PlaydateAPI *pd = NULL;

float calculateDisplacedWater(Player *player) {
	// Exit if above water level
	if (player->pos.y + player->radius < WATER_LEVEL) {
		return 0;
	}

	float playerVolume = 1.33333333333f * PI * player->radius * player->radius * player->radius;

	// If fully submerged
	if (player->pos.y - player->radius > WATER_LEVEL) {
		return playerVolume;
	}

	// Volume = ((pi * h^2)/3) * (3 * r - h)
	float h = player->radius - fabsf(player->pos.y - WATER_LEVEL);
	float spherialCapVolume = ((PI * h * h) / 3.0f) * (3.0f * player->radius - h);

	float submergedPlayerVolume;
	if (player->pos.y > WATER_LEVEL) {
		submergedPlayerVolume = playerVolume - spherialCapVolume;
	} else {
		submergedPlayerVolume = spherialCapVolume;
	}

	return submergedPlayerVolume;
}

// Public

void processPlayerPhysics(Player *player, float delta) {
	// Gravity
	player->vel.y += GRAVITY * delta;

	// Buoyancy
	float buoyancyForce = (7.0f * calculateDisplacedWater(player) * GRAVITY);
	player->vel.y -= buoyancyForce / PLAYER_MASS * delta;

	// Apply velocity
	player->pos.x += player->vel.x;
	player->pos.y += player->vel.y;

	// Hitting walls
	if (player->pos.x < 0) {
		player->pos.x = 0;
		player->vel.x = -player->vel.x / 6.0f;
	}
	if (player->pos.x > LCD_COLUMNS) {
		player->pos.x = LCD_COLUMNS;
		player->vel.x = -player->vel.x / 6.0f;
	}
}