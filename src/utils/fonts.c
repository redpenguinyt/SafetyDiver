//
//  fonts.c
//

#include "fonts.h"

LCDFont *pedallicaFont = NULL;

// Loads the fonts and sets fullCircleFont as the default font
void loadFonts(PlaydateAPI *pd) {
	pedallicaFont = pd->graphics->loadFont("fonts/pedallica", NULL);

	pd->graphics->setFont(pedallicaFont);
}

LCDFont *getPedallicaFont(void) { return pedallicaFont; }
