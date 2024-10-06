//
//  main.c
//

#include "game.h"

#include "pd_api.h"

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
