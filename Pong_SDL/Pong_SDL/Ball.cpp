#include "Ball.h"

Ball::Ball() :x(0), y(0), width(32), height(32), speedX(5),speedY(5)
{

}
Ball::Ball(int nX, int nY, int nWidth, int nHeight, int nSpeedX,int nSpeedY) :
	x(nX), y(nY), width(nWidth), height(nHeight), speedX(nSpeedX),speedY(nSpeedY)
{

}
Ball::~Ball()
{

}
void Ball::Update(int screenHeight)
{
	x += speedX;
	y += speedY;
	if (y < 16)
	{
		VerticalBounce(16);
	}
	else if (y > screenHeight - height - 16)
	{
		VerticalBounce(screenHeight - height - 16 ); 
	}
}
void Ball::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = ToRect();
	SDL_RenderFillRect(renderer, &rect);
}
void Ball::HorizontalBounce(int newXPos)
{
	speedX = -speedX;
	x = newXPos;
}
void Ball::VerticalBounce(int newYPos)
{
	speedY = -speedY;
	y = newYPos;
}
void Ball::ResetPosition(int screenWidth,int screenHeight)
{
	x = screenWidth / 2;
	y = screenHeight / 2;
	speedX = -speedX;
}
void Ball::SetSpeed(int nSpeedX,int nSpeedY)
{
	speedX = nSpeedX;
	speedY = nSpeedY;
}
SDL_Rect Ball::ToRect()
{
	return { x,y,width,height };
}
int Ball::GetX() const
{
	return x;
}
int Ball::GetXSpeed() const
{
	return speedX;
}