//
//  hazards.c
//

#include "hazards.h"

#include "utils/pd_pointer.h"
#include "utils/rensutils.h"

static Hazard hazards[24];

void randomiseHazard(Hazard *hazard) {
	hazard->pos.x = rand() % 400;
	hazard->pos.y = WATER_LEVEL + rand() % (FLOOR_LEVEL - WATER_LEVEL);
	hazard->width = rand() % 100 + 20;
	hazard->height = rand() % 60 + 10;
}

void playZapSound(void) {
	static AudioSample *zapSound;
	static SamplePlayer *zapSoundPlayer;

	if (zapSound == NULL || zapSoundPlayer == NULL) {
		zapSound = snd->sample->load("sounds/zap.wav");

		zapSoundPlayer = snd->sampleplayer->newPlayer();
		snd->sampleplayer->setSample(zapSoundPlayer, zapSound);
	}

	snd->sampleplayer->play(zapSoundPlayer, 1, 1.0);
}

// Public

void setupHazards(void) {
	for (size_t i = 0; i < (sizeof(hazards) / sizeof(Hazard)); i++) {
		randomiseHazard(&hazards[i]);
	}
}

bool processHazardCollisions(Player *player) {
	bool hasCollided = false;

	for (size_t i = 0; i < (sizeof(hazards) / sizeof(Hazard)); i++) {
		float hazardLeft = hazards[i].pos.x;
		float hazardTop = hazards[i].pos.y;
		float hazardRight = hazards[i].pos.x + hazards[i].width;
		float hazardBottom = hazards[i].pos.y + hazards[i].height;

		// Vertical collisions
		if (player->pos.x > hazardLeft && player->pos.x < hazardRight) {
			// Top edge
			if (player->pos.y > hazardTop && player->pos.y - player->vel.y < hazardTop) {
				hasCollided = true;
				player->vel.y /= -6;
				player->pos.y = hazardTop + player->vel.y;
			}
			// Bottom edge
			if (player->pos.y < hazardBottom && player->pos.y - player->vel.y > hazardBottom) {
				hasCollided = true;
				player->vel.y /= -6;
				player->pos.y = hazardBottom + player->vel.y;
			}
		}
		// Horizontal collisions
		if (player->pos.y > hazardTop && player->pos.y < hazardBottom) {
			// Left edge
			if (player->pos.x > hazardLeft && player->pos.x - player->vel.x <= hazardLeft) {
				hasCollided = true;
				player->vel.x /= -6;
				if (player->vel.x > -1.0f) {
					player->vel.x = -1.0f;
				}
				player->pos.x = hazardLeft + player->vel.y;
			}
			// Right edge
			if (player->pos.x < hazardRight && player->pos.x - player->vel.x >= hazardRight) {
				hasCollided = true;
				player->vel.x /= -6;
				if (player->vel.x < 1.0f) {
					player->vel.x = 1.0f;
				}
				player->pos.x = hazardRight + player->vel.y;
			}
		}
	}

	if (hasCollided) {
		playZapSound();
	}

	return hasCollided;
}

void drawHazards(int offsetY) {
	for (size_t i = 0; i < (sizeof(hazards) / sizeof(Hazard)); i++) {
		gfx->drawRect(hazards[i].pos.x, hazards[i].pos.y - offsetY, hazards[i].width, hazards[i].height, 0);
	}
}