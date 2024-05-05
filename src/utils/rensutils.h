//
//  rensutils.h
//

#ifndef rensutils_h
#define rensutils_h

#include <stdbool.h>

#define TARGET_EXTENSION 1
#include "pd_api.h"

#define PI 3.14159265358979323846f	 /* pi */
#define PI_2 1.57079632679489661923f /* pi/2 */
#define PI_4 0.78539816339744830962f /* pi/4 */

float rad2deg(float radians);
float deg2rad(float degrees);

LCDBitmap *loadImageAtPath(PlaydateAPI *pd, const char *path);
#define lazyLoadImageAtPath(VAR, FILE) \
	static LCDBitmap *VAR = NULL;      \
	if (VAR == NULL)                   \
		VAR = loadImageAtPath(pd, FILE);
LCDBitmapTable *loadSpritesheetAtPath(PlaydateAPI *pd, const char *path);
#define lazyLoadSpritesheetAtPath(VAR, FILE) \
	static LCDBitmapTable *VAR = NULL;       \
	if (VAR == NULL)                         \
		VAR = loadSpritesheetAtPath(pd, FILE);

bool isPosOnScreen(int x, int y);

#endif /* rensutils_h */