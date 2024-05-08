//
//  pd_pointer.c
//

#include "pd_pointer.h"

PlaydateAPI *pd = NULL;
const struct playdate_sys *sys;
const struct playdate_graphics *gfx;
const struct playdate_sound *snd;

void setupPointer(PlaydateAPI *p) {
	pd = p;
	sys = p->system;
	gfx = p->graphics;
	snd = p->sound;
}
