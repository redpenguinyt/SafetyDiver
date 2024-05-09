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
#include "utils/game_state.h"
#include "utils/pd_pointer.h"
#include "utils/rensutils.h"

static float deltaTime;

static Player player;
static int score = 0;
static int heldScore = 0;
static bool zapped = false;

void process(float deltaTime) {
	if (gameState == kGameStatePlaying) {
		playerMovement(&player, deltaTime);
		processPlayerPhysics(&player, deltaTime);
		processGold(player, &heldScore);
		if (processHazardCollisions(&player)) {
			if (heldScore > 0) {
				zapped = true;
			}
			heldScore = 0;
		}
		if (player.pos.y < WATER_LEVEL && player.pos.y - player.vel.y > WATER_LEVEL) {
			if (heldScore == 0 && zapped) {
				gameState = kGameStateOver;
			}

			score += heldScore;
			heldScore = 0;
			zapped = false;
		}
		playerSounds(player);
	} else if (gameState == kGameStateOver) {
		PDButtons pushed;
		sys->getButtonState(NULL, &pushed, NULL);

		if (pushed & kButtonA) {
			gameState = kGameStatePlaying;
			player = newPlayer();
			regenerateGoldPositions();
			regenerateHazards();
		}
	}
}

void draw(void) {
	switch (gameState) {
		case kGameStatePlaying:
			int offsetY = player.pos.y + player.vel.y * 5.0f - 120.0f;
			if (player.pos.y + player.vel.y * 5.0f > FLOOR_LEVEL - LCD_ROWS / 2) {
				offsetY = FLOOR_LEVEL - LCD_ROWS - 2;
			}
			drawWater(offsetY);
			drawGold(offsetY);
			drawHazards(offsetY);
			drawPlayer(player, sys->getCrankAngle(), heldScore);

			drawHUD(player, score);
			break;

		case kGameStateOver:
			static char *gameOverText;
			sys->formatString(&gameOverText, "You died, your score was %d", score);
			gfx->drawText(gameOverText, strlen(gameOverText), kASCIIEncoding, 10, 10);
			gfx->drawText("Press A to restart", 19, kUTF8Encoding, 10, 40);

			break;
	}
}

// Main functions

void setup(PlaydateAPI *p) {
	setupPointer(p);
	pd->display->setRefreshRate(50);
	loadFonts();

	player = newPlayer();
	regenerateGoldPositions();
	regenerateHazards();
}

int update(void *ud) {
	deltaTime = sys->getElapsedTime();
	sys->resetElapsedTime();
	gfx->clear(1);

	process(deltaTime);

	draw();

	return 1;
}