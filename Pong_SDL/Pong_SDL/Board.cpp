#include "Board.h"

Board::Board()
{

}
Board::~Board()
{

}
void Board::Draw(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
	SDL_Rect rect;
	int multiplier = 0;
	int numberOfStripes = (screenHeight - 32) / 32;

	for (int i = 0; i < numberOfStripes; i++)
	{
		rect = { screenWidth / 2,32 * multiplier + 16,16,32 };
		SDL_RenderFillRect(renderer, &rect);
		multiplier += 2;
	}

	rect = { 0,0,screenWidth,16 };
	SDL_RenderFillRect(renderer, &rect);
	rect.y = screenHeight - 16;
	SDL_RenderFillRect(renderer, &rect);
	
}