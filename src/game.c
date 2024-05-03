//
//  game.c
//

#include "game.h"

#include "physics.h"
#include "rensutils.h"

const LCDPattern grey20 = {
	0b01111111,
	0b10111111,
	0b11011111,
	0b11101111,
	0b11110111,
	0b11111011,
	0b11111101,
	0b11111110, // Bitmap, each byte is a row of pixel
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Mask, here fully opaque
};

static PlaydateAPI *pd = NULL;
static float deltaTime;

static Player player;

// Main functions

void setup(PlaydateAPI *p) {
	pd = p;
	pd->display->setRefreshRate(50);

	player.pos.x = LCD_COLUMNS / 2;
	player.pos.y = 60;
	player.radius = 15;
}

int update(void *ud) {
	deltaTime = pd->system->getElapsedTime();
	pd->system->resetElapsedTime();
	pd->graphics->clear(1);

	pd->graphics->fillRect(0, WATER_LEVEL, LCD_COLUMNS, LCD_ROWS - WATER_LEVEL, grey20);
	pd->graphics->drawLine(0, WATER_LEVEL, LCD_COLUMNS, WATER_LEVEL, 1, 0);

	float crankAngle = pd->system->getCrankAngle();
	PDButtons pressed;
	pd->system->getButtonState(&pressed, NULL, NULL);
	if (pressed & kButtonB) {
		float rudderStrength = 5.0;
		if (player.pos.y < WATER_LEVEL) {
			rudderStrength = 2.0;
		}
		player.vel.x += cosf(deg2rad(crankAngle - 90)) * rudderStrength * deltaTime;
		player.vel.y += sinf(deg2rad(crankAngle - 90)) * rudderStrength * deltaTime;
	}
	processPlayerPhysics(&player, deltaTime);

	lazyLoadImageAtPath(playerImage, "images/player.png");
	pd->graphics->drawRotatedBitmap(playerImage, player.pos.x, player.pos.y, crankAngle, 0.5, 0.4, 1.5, 1.5);

	return 1;
}