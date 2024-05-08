//
//  treasure.c
//

#include "treasure.h"

#include "utils/rensutils.h"
#include "utils/pd_pointer.h"

static AudioSample *coinSound;
static SamplePlayer *coinSoundPlayer;

static GoldPiece gold[64];

void randomiseGold(GoldPiece *goldPiece) {
	goldPiece->pos.x = rand() % 400;
	goldPiece->pos.y = WATER_LEVEL + rand() % (FLOOR_LEVEL - WATER_LEVEL);
	goldPiece->radius = rand() % 10 + 5;
	goldPiece->t = rand() % 6;
}

// Public

void setupTreasure(void) {
	coinSound = snd->sample->load("sounds/coin.wav");
	coinSoundPlayer = snd->sampleplayer->newPlayer();
	snd->sampleplayer->setSample(coinSoundPlayer, coinSound);

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
			pd->sound->sampleplayer->play(coinSoundPlayer, 1, 1.0f);
		}
	}
}

void drawGold(int offsetY) {
	for (size_t i = 0; i < (sizeof(gold) / sizeof(GoldPiece)); i++) {
		gold[i].t += 0.05f;

		// Coin spin effect
		float xRadius = ceilf(gold[i].radius * (cosf(gold[i].t) / 2.0f + 0.5f));

		pd->graphics->drawEllipse(gold[i].pos.x - xRadius, gold[i].pos.y - gold[i].radius - offsetY, xRadius * 2,
								  gold[i].radius * 2, 3, 0, 0, (LCDColor)0);
	}
}