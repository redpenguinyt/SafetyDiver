//
// draw.c
//

#include "draw.h"
#include "rensutils.h"

const LCDPattern grey20 = {
	0b01111111, 0b10111111, 0b11011111, 0b11101111, 0b11110111, 0b11111011, 0b11111101,
	0b11111110, // Bitmap, each byte is a row of pixel
	0xFF,		0xFF,		0xFF,		0xFF,		0xFF,		0xFF,		0xFF,		0xFF, // Mask, here fully opaque
};

static PlaydateAPI *pd = NULL;
static const struct playdate_graphics *gfx = NULL;

void setupDraw(PlaydateAPI *p) {
	pd = p;
	gfx = p->graphics;
}

void drawWater(Player player) {
	pd->graphics->fillRect(0, LCD_ROWS - player.pos.y, LCD_COLUMNS, player.pos.y, (LCDColor)grey20);
	pd->graphics->drawLine(0, LCD_ROWS - player.pos.y, LCD_COLUMNS, LCD_ROWS - player.pos.y, 1, 0);
}

void drawPlayer(Player player, float degrees, float rudderSpeed) {
	lazyLoadSpritesheetAtPath(playerImageTable, "images/player");

	static float frame = 0;
	frame += rudderSpeed / 10.0f;
	if (floorf(frame) > 3) {
		frame = 0;
	}

	LCDBitmap *playerFrame = pd->graphics->getTableBitmap(playerImageTable, (int)floorf(frame));
	pd->graphics->drawRotatedBitmap(playerFrame, player.pos.x, LCD_ROWS / 2, degrees, 0.5, 0.4, 1.5, 1.5);
}