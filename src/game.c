//
//  game.c
//

#include "game.h"

#include "draw.h"
#include "hazards.h"
#include "physics.h"
#include "player.h"
#include "treasure.h"
#include "utils/audio.h"
#include "utils/fonts.h"
#include "utils/rensutils.h"

static PlaydateAPI *pd = NULL;
static float deltaTime;

static Player player;
static int score = 0;
static int heldScore = 0;

// Main functions

void setup(PlaydateAPI *p) {
	pd = p;
	pd->display->setRefreshRate(50);

	loadSounds(p);
	loadFonts(p);
	setupDraw(p);
	setupTreasure(p);
	generateHazards();
	setupPlayer(p);

	player = newPlayer();
}

int update(void *ud) {
	deltaTime = pd->system->getElapsedTime();
	pd->system->resetElapsedTime();
	pd->graphics->clear(1);

	float rudderStrength = playerMovement(&player, deltaTime);
	processPlayerPhysics(&player, deltaTime);
	processGold(player, &heldScore);
	if (processHazards(player)) {
		heldScore = 0;
	}
	if (player.pos.y < WATER_LEVEL) {
		score += heldScore;
		heldScore = 0;
	}
	playerSounds(player);

	int offsetY = player.pos.y + player.vel.y * 5.0f - 120.0f;
	drawWater(offsetY);
	drawGold(pd, offsetY);
	drawHazards(pd, offsetY);
	drawPlayer(player, pd->system->getCrankAngle(), rudderStrength, heldScore);

	drawHUD(player, score);

	return 1;
}