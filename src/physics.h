//
//  physics.h
//

#ifndef physics_h
#define physics_h

#define GRAVITY 9.8f
#define WATER_LEVEL 100
#define FLOOR_LEVEL 1520
#define WATER_DENSITY 3.0f
#define PLAYER_MASS 50000

typedef struct {
	float x, y;
} Vec2F;

typedef struct {
	Vec2F pos, vel;
	float radius;
} Player;

void processPlayerPhysics(Player *player, float delta);

#endif /* physics_h */
