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

void drawWater(float offsetY) {
	static LCDBitmap *waterImage = NULL;
	if (waterImage == NULL) {
		waterImage = gfx->newBitmap(400, 248, kColorClear);

		gfx->pushContext(waterImage);
		gfx->fillRect(0, 0, 400, 248, grey20);
		gfx->popContext();
	}

	int imageY = LCD_ROWS - roundf(offsetY);
	if (imageY < 0) {
		imageY = (LCD_ROWS - (int)roundf(offsetY)) % 8;
	}

	gfx->drawBitmap(waterImage, 0, imageY, kBitmapUnflipped);
	gfx->drawLine(0, LCD_ROWS - offsetY, LCD_COLUMNS, LCD_ROWS - offsetY, 1, 0);
}

void drawPlayer(Player player, float degrees, float rudderSpeed) {
	lazyLoadSpritesheetAtPath(playerImageTable, "images/player");

	static float frame = 0;
	frame += rudderSpeed / 10.0f;
	if (floorf(frame) > 3) {
		frame = 0;
	}

	LCDBitmap *playerFrame = gfx->getTableBitmap(playerImageTable, (int)floorf(frame));
	gfx->drawRotatedBitmap(playerFrame, player.pos.x, LCD_ROWS / 2, degrees, 0.5, 0.4, 2, 2);
}