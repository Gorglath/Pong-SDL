#ifndef ID_PONG_TEXT_H
#define ID_PONG_TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
class Text
{
	Text(int nX, int nY, int nWidth, int nHeight);
	~Text();
	void Load(SDL_Renderer* renderer, const char* newText);
	void ChangeText(SDL_Renderer* renderer, const char* newText);
	void Draw(SDL_Renderer* renderer);
private:
	Text();
	int x;
	int y;
	int width;
	int height;
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* surface;
	SDL_Texture* texture;
};
#endif // !ID_PONG_TEXT_H

