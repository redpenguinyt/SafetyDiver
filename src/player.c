//
//  player.c
//

#include "player.h"

#include "utils/rensutils.h"

static PlaydateAPI *pd = NULL;

void setupPlayer(PlaydateAPI *p) { pd = p; }

Player newPlayer(void) {
	Player player;

	player.pos.x = LCD_COLUMNS / 2;
	player.pos.y = 60;
	player.vel.x = 0;
	player.vel.y = 0;
	player.radius = 15;

	return player;
}

float playerMovement(Player *player, float deltaTime) {
	float rudderStrength = 0;
	float crankAngle = pd->system->getCrankAngle();

	PDButtons pressed;
	pd->system->getButtonState(&pressed, NULL, NULL);
	if (pressed & kButtonB) {
		rudderStrength = 5.0f;
		if (player->pos.y < WATER_LEVEL) {
			rudderStrength = 2.0f;
		}
		player->vel.x += cosf(deg2rad(crankAngle - 90)) * rudderStrength * deltaTime;
		player->vel.y += sinf(deg2rad(crankAngle - 90)) * rudderStrength * deltaTime;
	}

	return rudderStrength;
}

void playerSounds(Player player) {
	if (player.pos.y > WATER_LEVEL && player.pos.y - player.vel.y < WATER_LEVEL && player.vel.y > 5.0f) {
		static AudioSample *splashSound;
		static SamplePlayer *splashSoundPlayer;

		if (splashSound == NULL || splashSoundPlayer == NULL) {
			splashSound = pd->sound->sample->load("sounds/splash.wav");

			splashSoundPlayer = pd->sound->sampleplayer->newPlayer();
			pd->sound->sampleplayer->setSample(splashSoundPlayer, splashSound);
		}

		pd->sound->sampleplayer->play(splashSoundPlayer, 1, 1.0);
	}
}