//
//  pd_pointer.h
//

#ifndef pd_pointer_h
#define pd_pointer_h

#define TARGET_EXTENSION 1
#include "pd_api.h"

/// A pointer to the Playdate API
extern PlaydateAPI *pd;
extern const struct playdate_sys *sys;
extern const struct playdate_graphics *gfx;
extern const struct playdate_sound *snd;

void setupPointer(PlaydateAPI *p);

#endif /* pd_pointer_h */