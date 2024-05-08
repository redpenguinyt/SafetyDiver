//
//  player.c
//

#include "player.h"

#include "../utils/pd_pointer.h"
#include "../utils/rensutils.h"

Player newPlayer(void) {
	Player player;

	player.pos.x = LCD_COLUMNS / 2;
	player.pos.y = 60;
	player.vel.x = 0;
	player.vel.y = 0;
	player.radius = 15;

	return player;
}

void playerMovement(Player *player, float deltaTime) {
	player->rudderStrength = 0;
	float crankAngle = deg2rad(sys->getCrankAngle() - 90);

	PDButtons pressed;
	sys->getButtonState(&pressed, NULL, NULL);
	if (pressed & kButtonB) {
		player->rudderStrength = 5.0f;
		if (player->pos.y < WATER_LEVEL) {
			player->rudderStrength = 2.0f;
		}

		player->vel.x += cosf(crankAngle) * player->rudderStrength * deltaTime;
		player->vel.y += sinf(crankAngle) * player->rudderStrength * deltaTime;
	}
}

void playerSounds(Player player) {
	if (player.pos.y > WATER_LEVEL && player.pos.y - player.vel.y < WATER_LEVEL && player.vel.y > 5.0f) {
		static AudioSample *splashSound;
		static SamplePlayer *splashSoundPlayer;

		if (splashSound == NULL || splashSoundPlayer == NULL) {
			splashSound = snd->sample->load("sounds/splash.wav");

			splashSoundPlayer = snd->sampleplayer->newPlayer();
			snd->sampleplayer->setSample(splashSoundPlayer, splashSound);
		}

		snd->sampleplayer->play(splashSoundPlayer, 1, 1.0);
	}
}