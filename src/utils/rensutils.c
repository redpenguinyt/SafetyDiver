//
//  rensutils.c
//

#include "rensutils.h"

#include "pd_pointer.h"

float rad2deg(float radians) { return radians * 180.0f / PI; }

float deg2rad(float degrees) { return degrees * PI / 180.0f; }

LCDBitmap *loadImageAtPath(const char *path) {
	const char *outErr = NULL;
	LCDBitmap *img = gfx->loadBitmap(path, &outErr);
	if (outErr != NULL) {
		sys->logToConsole("Error loading image at path '%s': %s", path, outErr);
	}
	return img;
}
LCDBitmapTable *loadSpritesheetAtPath(const char *path) {
	const char *outErr = NULL;
	LCDBitmapTable *img = gfx->loadBitmapTable(path, &outErr);
	if (outErr != NULL) {
		sys->logToConsole("Error loading spritesheet at path '%s': %s", path, outErr);
	}
	return img;
}

bool isPosOnScreen(int x, int y) { return x >= 0 && x < LCD_COLUMNS && y >= 0 && y < LCD_ROWS; }