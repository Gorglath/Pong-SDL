#include "Text.h"

Text::Text()
{

}
Text::Text(int nX, int nY, int nWidth, int nHeight)
: x(nX),y(nY),width(nWidth),height(nHeight)
{

}
Text::~Text()
{

}
void Text::Load(SDL_Renderer* renderer, const char* newText)
{
	font = TTF_OpenFont("OpenSans-Regular.ttf", 28);
	ChangeText(renderer, newText);
}
void Text::ChangeText(SDL_Renderer* renderer, const char* newText)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
	surface = TTF_RenderText_Solid(font, newText, color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}
void Text::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { x,y,width,height };
	SDL_RenderCopy(renderer, texture,nullptr, &rect);
}