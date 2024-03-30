//
//  game.c
//

#include "game.h"
#include <stdio.h>
#include <string.h>

static PlaydateAPI *pd = NULL;

// Main functions

void setup(PlaydateAPI *p) {
	pd = p;

	pd->display->setRefreshRate(60);
}

int update(void *ud) {
	char str[] = "Hello world!";
	pd->graphics->drawText(str, strlen(str), kASCIIEncoding, LCD_COLUMNS / 2, LCD_ROWS / 2);

	return 1;
}