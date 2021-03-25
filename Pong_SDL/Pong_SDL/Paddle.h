#ifndef ID_PONG_PADDLE_H
#define ID_PONG_PADDLE_H
#include <SDL.h>
class Paddle
{
public:
	Paddle();
	Paddle(int nX, int nY, int nWidth, int nHeight, int nSpeedY);
	~Paddle();
	void Update(int screenHeight);
	void Draw(SDL_Renderer* renderer);
	SDL_Rect ToRect();
private:
	int x;
	int y;
	int width;
	int height;
	int speedY;
};
#endif // !ID_PONG_PADDLE_H

