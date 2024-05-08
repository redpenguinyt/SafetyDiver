//
//  game.c
//

#include "game.h"

#include "level/draw.h"
#include "level/hazards.h"
#include "level/physics.h"
#include "level/player.h"
#include "level/treasure.h"
#include "utils/fonts.h"
#include "utils/pd_pointer.h"
#include "utils/rensutils.h"

static float deltaTime;

static Player player;
static int score = 0;
static int heldScore = 0;

void process(float deltaTime) {
	playerMovement(&player, deltaTime);
	processPlayerPhysics(&player, deltaTime);
	processGold(player, &heldScore);
	if (processHazardCollisions(&player)) {
		heldScore = 0;
	}
	if (player.pos.y < WATER_LEVEL) {
		score += heldScore;
		heldScore = 0;
	}
	playerSounds(player);
}

void draw(void) {
	int offsetY = player.pos.y + player.vel.y * 5.0f - 120.0f;
	if (player.pos.y + player.vel.y * 5.0f > FLOOR_LEVEL - LCD_ROWS / 2) {
		offsetY = FLOOR_LEVEL - LCD_ROWS - 2;
	}
	drawWater(offsetY);
	drawGold(offsetY);
	drawHazards(offsetY);
	drawPlayer(player, sys->getCrankAngle(), heldScore);

	drawHUD(player, score);
}

// Main functions

void setup(PlaydateAPI *p) {
	setupPointer(p);
	pd->display->setRefreshRate(50);

	loadFonts();
	setupTreasure();
	setupHazards();

	player = newPlayer();
}

int update(void *ud) {
	deltaTime = sys->getElapsedTime();
	sys->resetElapsedTime();
	gfx->clear(1);

	process(deltaTime);

	draw();

	return 1;
}