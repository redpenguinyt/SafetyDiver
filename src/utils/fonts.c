//
//  fonts.c
//

#include "fonts.h"

#include "pd_pointer.h"

LCDFont *pedallicaFont = NULL;

// Loads the fonts and sets fullCircleFont as the default font
void loadFonts(void) {
	pedallicaFont = gfx->loadFont("fonts/pedallica", NULL);

	gfx->setFont(pedallicaFont);
}

LCDFont *getPedallicaFont(void) { return pedallicaFont; }
