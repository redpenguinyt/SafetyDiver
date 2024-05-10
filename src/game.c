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
	snd->channel->setVolume(snd->getDefaultChannel(), 0.1);
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

			lazyLoadImageAtPath(gameOverImage, "images/game_over.png");
			gfx->drawBitmap(gameOverImage, 0, 0, kBitmapUnflipped);

			static char *gameOverText;
			sys->formatString(&gameOverText, "You collected %d gold pieces", score);
			gfx->drawText(gameOverText, strlen(gameOverText), kASCIIEncoding, 149, 91);

			break;
	}

	return 1;
}