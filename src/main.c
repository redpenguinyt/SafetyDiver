//
//  main.c
// 

#include <stdio.h>
#include <stdlib.h>

#define TARGET_EXTENSION 1
#include "pd_api.h"

#include "game.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
	int eventHandler(PlaydateAPI *playdate, PDSystemEvent event, uint32_t arg) {
	if (event == kEventInit) {
		setup(playdate);
		playdate->system->setUpdateCallback(update, NULL);
	}

	return 0;
}
