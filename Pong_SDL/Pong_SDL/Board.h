#ifndef INC_PONG_BOARD_H
#define INC_PONG_BOARD_H
#include <SDL.h>
class Board
{
public:
	Board();
	~Board();
	void Draw(SDL_Renderer* renderer,int screenWidth,int screenHeight);
};
#endif // !ID_PONG_BOARD_H

