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
void Ball::Update(int screenWidth,int screenHeight)
{
	x += speedX;
	y += speedY;
	if (y < 0)
	{
		VerticalBounce(0);
	}
	else if (y > screenHeight - height)
	{
		VerticalBounce(screenHeight - height);
	}
	if (x < 0)
	{
		HorizontalBounce(0);
	}
	else if (x > screenWidth - width)
	{
		HorizontalBounce(screenWidth - width);
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
SDL_Rect Ball::ToRect()
{
	return { x,y,width,height };
}