#include "Paddle.h"

Paddle::Paddle() :x(0), y(0), width(32), height(128), speedY(4)
{

}
Paddle::Paddle(int nX, int nY, int nWidth, int nHeight, int nSpeedY) :
	x(nX), y(nY), width(nWidth), height(nHeight), speedY(nSpeedY)
{

}
Paddle::~Paddle()
{

}
void Paddle::Update(int screenHeight,PaddleInput* input)
{
	if (input->MoveUp)
	{
		MoveUp();
	}
	else if (input->MoveDown)
	{
		MoveDown(screenHeight);
	}
}
void Paddle::UpdateAI(int screenHeight, int ballY)
{
	if (ballY < y + height / 4)
	{
		MoveUp();
	}
	else if (ballY > y + height * 3 / 4)
	{
		MoveDown(screenHeight);
	}
}
void Paddle::MoveUp() 
{
	y -= speedY;
	if (y < 0)
	{
		y = 0;
	}
}
void Paddle::MoveDown(int screenHeight)
{
	y += speedY;
	if (y > screenHeight - height)
	{
		y = screenHeight - height;
	}
}
void Paddle::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = ToRect();
	SDL_RenderFillRect(renderer, &rect);
}
SDL_Rect Paddle::ToRect()
{
	return { x,y,width,height };
}