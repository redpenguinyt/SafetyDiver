//
//  pd_pointer.h
//

#ifndef pd_pointer_h
#define pd_pointer_h

#define TARGET_EXTENSION 1
#include "pd_api.h"

/// A pointer to the Playdate API
extern PlaydateAPI *pd;
extern const struct playdate_graphics *gfx;
extern const struct playdate_sound *snd;

void setupPointer(PlaydateAPI *p);
PlaydateAPI *getPD(void);
const struct playdate_graphics *getGFX(void);
const struct playdate_sound *getSND(void);

#endif /* pd_pointer_h */