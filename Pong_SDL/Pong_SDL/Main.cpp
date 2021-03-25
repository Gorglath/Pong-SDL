#include <SDL.h>
#include "Ball.h"
#include "Paddle.h"
#include "Collision.h"
#include "Board.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 448;
bool quit = false;

Board board;
Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;
PaddleInput input;

void Update();
void Draw(SDL_Renderer* renderer);
void Close(SDL_Renderer* renderer, SDL_Window* window);
bool HandleInput();
inline void CheckCollision(SDL_Rect* ballRect, SDL_Rect* paddleRect, int newBallX);

int main(int argc, char* args[])
{
	//Initialize SDL Window.
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("Pong-SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	board = Board();
	ball = Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 16, 16, 5, 5);
	leftPaddle = Paddle(16, 200, 16, 64, 4);
	rightPaddle = Paddle(SCREEN_WIDTH - 32, 200, 16, 64, 4);
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
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_w)
			{
				input.MoveUp = true;
			}
			else if(e.key.keysym.sym == SDLK_s)
			{
				input.MoveDown = true;
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_w)
			{
				input.MoveUp = false;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				input.MoveDown = false;
			}
		}
		else if (e.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}
void Update()
{
	ball.Update(SCREEN_WIDTH,SCREEN_HEIGHT);
	leftPaddle.Update(SCREEN_HEIGHT, &input);

	SDL_Rect ballRect = ball.ToRect();
	SDL_Rect paddleRect = leftPaddle.ToRect();
	CheckCollision(&ballRect, &paddleRect, paddleRect.x + paddleRect.w);

	rightPaddle.UpdateAI(SCREEN_HEIGHT,ballRect.y);
	paddleRect = rightPaddle.ToRect();
	CheckCollision(&ballRect, &paddleRect, paddleRect.x - paddleRect.w);
}
inline void CheckCollision(SDL_Rect* ballRect, SDL_Rect* paddleRect, int ballNewX)
{
	bool colliding = Collision::AABBCollision(ballRect, paddleRect);
	if (colliding)
	{
		ball.HorizontalBounce(ballNewX);
	}
}
void Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xA0);
	board.Draw(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	ball.Draw(renderer);
	leftPaddle.Draw(renderer);
	rightPaddle.Draw(renderer);
	
	SDL_RenderPresent(renderer);
}
void Close(SDL_Renderer* renderer,SDL_Window* window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}