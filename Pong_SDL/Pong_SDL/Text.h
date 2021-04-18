#ifndef INC_PONG_TEXT_H
#define INC_PONG_TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
class Text
{
public:
	Text();
	Text(int nX, int nY, int nWidth, int nHeight);
	~Text();
	void Load(SDL_Renderer* renderer, const char* newText, SDL_Color nColor);
	void ChangeText(SDL_Renderer* renderer, const char* newText, SDL_Color nColor);
	void Draw(SDL_Renderer* renderer);
	SDL_Rect ToRect();
private:
	int x;
	int y;
	int width;
	int height;
	char* text;
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
};
#endif // !ID_PONG_TEXT_H

