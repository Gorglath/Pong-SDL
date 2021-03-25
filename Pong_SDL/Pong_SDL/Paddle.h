#ifndef ID_PONG_PADDLE_H
#define ID_PONG_PADDLE_H
#include <SDL.h>
#include "PaddleInput.h"
class Paddle
{
public:
	Paddle();
	Paddle(int nX, int nY, int nWidth, int nHeight, int nSpeedY);
	~Paddle();
	void Update(int screenHeight,PaddleInput* input);
	void UpdateAI(int screenHeight, int ballY);
	void Draw(SDL_Renderer* renderer);
	void MoveUp();
	void MoveDown(int screenHeight);
	SDL_Rect ToRect();
private:
	int x;
	int y;
	int width;
	int height;
	int speedY;
};
#endif // !ID_PONG_PADDLE_H

