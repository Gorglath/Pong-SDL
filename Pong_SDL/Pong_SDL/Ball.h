#ifndef INC_PONG_BALL_H
#define INC_PONG_BALL_H
#include <SDL.h>
#include"Sound.h"
class Ball
{
public:
	Ball();
	Ball(int nX, int nY, int nWidth, int nHeight,int nSpeedX,int nSpeedY,Sound newWallHitSound);
	~Ball();
	void Update(int screenHeight);
	void Draw(SDL_Renderer* renderer);
	void HorizontalBounce(int newXPos);
	void VerticalBounce(int newYPos);
	void ResetPosition(int screenWidth,int screenHeight);
	void SetSpeed(int nSpeedX,int nSpeedY);
	SDL_Rect ToRect();
	int GetX() const;
	int GetXSpeed() const;
private:
	int x;
	int y;
	int width;
	int height;
	int speedX;
	int speedY;
	Sound wallHitSound;
};
#endif // !ID_PONG_BALL_H

