#ifndef INC_PONG_COLLISION_H
#define INC_PONG_COLLISION_H
#include <SDL.h>
class Collision
{
public:
	static bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB)
	{
		int xMinA = rectA->x;
		int xMaxA = rectA->x + rectA->w;
		int yMinA = rectA->y;
		int yMaxA = rectA->y + rectA->h;
		int xMinB = rectB->x;
		int xMaxB = rectB->x + rectB->w;
		int yMinB = rectB->y;
		int yMaxB = rectB->y + rectB->h;
		return !(xMinA > xMaxB || xMaxA < xMinB || yMinA > yMaxB || yMaxA < yMinB);
	}
private:
	Collision();
};
#endif // !ID_PONG_COLLISION_H
