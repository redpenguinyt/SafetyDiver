//
//  pd_pointer.c
//

#include "pd_pointer.h"

void setupPointer(PlaydateAPI *p) {
	pd = p;
	gfx = p->graphics;
	snd = p->sound;
}