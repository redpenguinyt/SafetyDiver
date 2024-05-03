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

void drawWater(void) {
	pd->graphics->fillRect(0, WATER_LEVEL, LCD_COLUMNS, LCD_ROWS - WATER_LEVEL, grey20);
	pd->graphics->drawLine(0, WATER_LEVEL, LCD_COLUMNS, WATER_LEVEL, 1, 0);
}

void drawPlayer(Player player, float degrees) {
	lazyLoadImageAtPath(playerImage, "images/player.png");
	pd->graphics->drawRotatedBitmap(playerImage, player.pos.x, player.pos.y, degrees, 0.5, 0.4, 1.5, 1.5);
}