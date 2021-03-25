#include <SDL.h>
#include "Ball.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 420;
bool quit = false;

Ball ball;

void Update();
void Draw(SDL_Renderer* renderer);
void Close(SDL_Renderer* renderer, SDL_Window* window);
bool HandleInput();

int main(int argc, char* args[])
{
	//Initialize SDL Window.
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("Pong-SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	ball = Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 16, 16, 5, 5);
	//Main game loop.
	while (!quit)
	{
		//Check if the player quit.
		quit = HandleInput();

		//Update objects.
		Update();

		//Draw objects.
		Draw(renderer);

	}

	Close(renderer, window);

	return 0;
}
bool HandleInput()
{
	SDL_Event e;
	if (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}
void Update()
{
	ball.Update(SCREEN_WIDTH,SCREEN_HEIGHT);
}
void Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	ball.Draw(renderer);
	
	SDL_RenderPresent(renderer);
}
void Close(SDL_Renderer* renderer,SDL_Window* window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}