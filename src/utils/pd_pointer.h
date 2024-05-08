//
//  pd_pointer.h
//

#ifndef pd_pointer_h
#define pd_pointer_h

#define TARGET_EXTENSION 1
#include "pd_api.h"

/// A pointer to the Playdate API
static PlaydateAPI *pd = NULL;
static const struct playdate_graphics *gfx = NULL;
static const struct playdate_sound *snd = NULL;


void setupPointer(PlaydateAPI *p);

#endif /* pd_pointer_h */