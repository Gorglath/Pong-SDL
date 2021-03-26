#ifndef ID_PONG_BALL_H
#define ID_PONG_BALL_H
#include <SDL.h>
class Ball
{
public:
	Ball();
	Ball(int nX, int nY, int nWidth, int nHeight,int nSpeedX,int nSpeedY);
	~Ball();
	void Update(int screenHeight);
	void Draw(SDL_Renderer* renderer);
	void HorizontalBounce(int newXPos);
	void VerticalBounce(int newYPos);
	void ResetPosition(int screenWidth,int screenHeight);
	void SetSpeed(int nSpeed);
	SDL_Rect ToRect();
	int GetX() const;
private:
	int x;
	int y;
	int width;
	int height;
	int speedX;
	int speedY;
};
#endif // !ID_PONG_BALL_H

