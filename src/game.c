//
//  game.c
//

#include "game.h"

#include "draw.h"
#include "hazards.h"
#include "physics.h"
#include "treasure.h"
#include "utils/fonts.h"
#include "utils/rensutils.h"

static PlaydateAPI *pd = NULL;
static float deltaTime;

static Player player;
static int score = 0;

// Main functions

void setup(PlaydateAPI *p) {
	pd = p;
	pd->display->setRefreshRate(50);

	loadFonts(p);
	setupDraw(p);
	generateGold();
	generateHazards();

	player.pos.x = LCD_COLUMNS / 2;
	player.pos.y = 60;
	player.radius = 15;
}

int update(void *ud) {
	deltaTime = pd->system->getElapsedTime();
	pd->system->resetElapsedTime();
	pd->graphics->clear(1);

	float rudderStrength = 0.0;
	float crankAngle = pd->system->getCrankAngle();
	PDButtons pressed;
	pd->system->getButtonState(&pressed, NULL, NULL);
	if (pressed & kButtonB) {
		rudderStrength = 5.0;
		if (player.pos.y < WATER_LEVEL) {
			rudderStrength = 2.0;
		}
		player.vel.x += cosf(deg2rad(crankAngle - 90)) * rudderStrength * deltaTime;
		player.vel.y += sinf(deg2rad(crankAngle - 90)) * rudderStrength * deltaTime;
	}
	processPlayerPhysics(&player, deltaTime);
	processGold(player, &score);
	if (processHazards(player)) {
		score = 0;
	}

	int offsetY = player.pos.y + player.vel.y * 5.0f - 120.0f;
	drawWater(offsetY);
	drawGold(pd, offsetY);
	drawHazards(pd, offsetY);
	drawPlayer(player, crankAngle, rudderStrength);

	drawHUD(player, score);

	return 1;
}