//
// draw.c
//

#include "draw.h"

#include "utils/fonts.h"	 // for Pedallica font
#include "utils/rensutils.h" // for lazyLoadSpritesheetAtPath
#include "utils/pd_pointer.h"

const LCDPattern grey20 = {
	0b01111111, 0b10111111, 0b11011111, 0b11101111, 0b11110111, 0b11111011, 0b11111101,
	0b11111110, // Bitmap, each byte is a row of pixel
	0xFF,		0xFF,		0xFF,		0xFF,		0xFF,		0xFF,		0xFF,		0xFF, // Mask, here fully opaque
};

void drawWater(float offsetY) {
	static LCDBitmap *waterImage = NULL;
	if (waterImage == NULL) {
		waterImage = gfx->newBitmap(400, 248, kColorClear);

		gfx->pushContext(waterImage);
		gfx->fillRect(0, 0, 400, 248, (LCDColor)grey20);
		gfx->popContext();
	}

	int imageY = WATER_LEVEL - roundf(offsetY);
	if (imageY < 0) {
		imageY = (WATER_LEVEL - (int)roundf(offsetY)) % 8;
	}

	gfx->drawBitmap(waterImage, 0, imageY, kBitmapUnflipped);
	gfx->drawLine(0, WATER_LEVEL - offsetY, LCD_COLUMNS, WATER_LEVEL - offsetY, 1, 0);
	gfx->drawLine(0, FLOOR_LEVEL - offsetY, LCD_COLUMNS, FLOOR_LEVEL - offsetY, 1, 0);
}

void drawPlayer(Player player, float degrees, float rudderSpeed, int heldScore) {
	lazyLoadSpritesheetAtPath(playerImageTable, "images/player");

	static float frame = 0;
	frame += rudderSpeed / 10.0f;
	if (floorf(frame) > 3) {
		frame = 0;
	}

	float offsetY = LCD_ROWS / 2 - player.vel.y * 5.0f;
	if (player.pos.y > FLOOR_LEVEL - LCD_ROWS / 2) {
		offsetY = player.pos.y - FLOOR_LEVEL + LCD_ROWS;
	}

	LCDBitmap *playerFrame = gfx->getTableBitmap(playerImageTable, (int)floorf(frame));
	gfx->drawRotatedBitmap(playerFrame, player.pos.x, offsetY, degrees, 0.5, 0.4, 2, 2);

	// Held Score
	if (heldScore > 0) {
		char *heldScoreText;
		sys->formatString(&heldScoreText, "%d", heldScore);

		gfx->drawText(heldScoreText, strlen(heldScoreText), kASCIIEncoding, player.pos.x + 15, offsetY - 15);
	}
}

void drawHUD(Player player, int score) {
	static bool drawOnRight = false;
	if (player.pos.x < 60) {
		drawOnRight = true;
	} else if (player.pos.x > 340) {
		drawOnRight = false;
	}

	static LCDBitmap *depthImage = NULL;
	if (depthImage == NULL) {
		depthImage = gfx->newBitmap(30, 234, 1);

		gfx->pushContext(depthImage);

		gfx->fillRect(0, WATER_LEVEL / 10.0f + 80, 30, LCD_ROWS - WATER_LEVEL + 6.0f, (LCDColor)grey20);
		gfx->drawRect(0, WATER_LEVEL / 10.0f + 80, 30, 1, 0);
		gfx->drawRect(0, 0, 30, 234, 0);

		gfx->popContext();
	}

	int offsetXHUD = drawOnRight ? 367 : 3;
	gfx->drawBitmap(depthImage, offsetXHUD, 3, kBitmapUnflipped);
	gfx->fillRect(offsetXHUD, player.pos.y / 10.0f + 82, 30, 3, 0);

	// Score
	char *scoreText;
	sys->formatString(&scoreText, "Score: %d", score);

	int textWidth = gfx->getTextWidth(getPedallicaFont(), scoreText, strlen(scoreText), kASCIIEncoding, 0);

	int coords[] = {160, 0, 240, 0, 230, 20, 170, 20};
	gfx->fillPolygon(4, coords, 1, kPolygonFillEvenOdd);
	gfx->drawLine(240, 0, 230, 20, 2, 0);
	gfx->drawLine(230, 20, 170, 20, 2, 0);
	gfx->drawLine(170, 20, 160, 0, 2, 0);
	gfx->drawText(scoreText, strlen(scoreText), kASCIIEncoding, (LCD_COLUMNS - textWidth) / 2, 3);
}