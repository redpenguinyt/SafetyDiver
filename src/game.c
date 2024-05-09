//
//  game.c
//

#include "game.h"

#include "level/level.h"
#include "utils/fonts.h"
#include "utils/game_state.h"
#include "utils/pd_pointer.h"
#include "utils/rensutils.h"

static float deltaTime;

// Main functions

void setup(PlaydateAPI *p) {
	setupPointer(p);
	pd->display->setRefreshRate(50);
	loadFonts();

	restartLevel();
}

int update(void *ud) {
	deltaTime = sys->getElapsedTime();
	sys->resetElapsedTime();
	gfx->clear(1);

	switch (gameState) {
		case kGameStatePlaying:
			processLevel(deltaTime);
			drawLevel();
			break;

		case kGameStateOver:
			PDButtons pushed;
			sys->getButtonState(NULL, &pushed, NULL);

			if (pushed & kButtonA) {
				gameState = kGameStatePlaying;
				restartLevel();
			}

			static char *gameOverText;
			sys->formatString(&gameOverText, "You died, your score was %d", score);
			gfx->drawText(gameOverText, strlen(gameOverText), kASCIIEncoding, 10, 10);
			gfx->drawText("Press A to restart", 19, kUTF8Encoding, 10, 40);

			break;
	}

	return 1;
}