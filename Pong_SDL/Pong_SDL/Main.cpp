#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstdio>
#include <cmath>
#include "Ball.h"
#include "Paddle.h"
#include "Collision.h"
#include "Board.h"
#include "Text.h"
#include "Triangle.h"
#include "Sound.h"
//Global Variables
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 448;
char newText[2];
bool quit = false;
//Menu numbers: 0 = Main Menu, 1 = Game Menu, 2 = Game Over Menu.
int currentMenu = 0;

PaddleInput input;

//Main Menu Variables
//Text Numbers: 0 = Start Game Text, 1 = Quit Game Text.
int currentTextSelect = 0;
Text titleText = Text(SCREEN_WIDTH / 2 - SCREEN_WIDTH/4/2 , SCREEN_HEIGHT / 4/4 , SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
Text subTitleText = Text(SCREEN_WIDTH / 2 - SCREEN_WIDTH/10/2, SCREEN_HEIGHT / 4/4 + SCREEN_HEIGHT/4/4*3 + SCREEN_HEIGHT / 10 / 2, SCREEN_WIDTH / 10,SCREEN_HEIGHT/10);
Text startGameText = Text(SCREEN_WIDTH / 4 - SCREEN_WIDTH / 8 / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 8 / 2, SCREEN_WIDTH / 8, SCREEN_WIDTH / 8);
Text quitGameText = Text(SCREEN_WIDTH / 4 * 3 - SCREEN_WIDTH / 8 / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 8 / 2, SCREEN_WIDTH / 8, SCREEN_WIDTH / 8);

//Game Menu Variables
int playerScore = 0;
int opponentScore = 0;

Board board;
Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;

Text playerScoreText = Text(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 25, 50);
Text opponentScoreText = Text(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4, 25, 50);

Sound wallBounceSound = Sound("Sound\\WallBounce.wav");
Sound paddleBounceSound = Sound("Sound\\PaddleBounce.wav");
Sound playerGoal = Sound("Sound\\PlayerGoal.wav");
Sound opponentGoal = Sound("Sound\\OpponentGoal.wav");
//Game Over Menu
Text gameOverTitleText = Text(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 / 2, SCREEN_HEIGHT / 4 / 4, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
Text restartGameText = Text(SCREEN_WIDTH / 4 - SCREEN_WIDTH / 8 / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 8 / 2, SCREEN_WIDTH / 8, SCREEN_WIDTH / 8);
Text returnToMenu = Text(SCREEN_WIDTH / 4 * 3 - SCREEN_WIDTH / 8 / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 8 / 2, SCREEN_WIDTH / 8, SCREEN_WIDTH / 8);

void Load(SDL_Renderer* renderer);
void Update(SDL_Renderer* renderer);
void UpdateGameMenu(SDL_Renderer* renderer);
void UpdateMainMenu(SDL_Renderer* renderer);
void UpdateGameOverMenu(SDL_Renderer* renderer);
void RestartGame(SDL_Renderer* renderer);
void Draw(SDL_Renderer* renderer);
void Close(SDL_Renderer* renderer, SDL_Window* window);
bool HandleInput();
inline void CheckCollision(SDL_Rect* ballRect, SDL_Rect* paddleRect, int newBallX);
inline double RemapValue(double value, double low1, double high1, double low2, double high2);

int main(int argc, char* args[])
{
	//Initialize SDL Window.
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
	Mix_OpenAudio(44000, MIX_DEFAULT_FORMAT, 2, 2048);
	
	window = SDL_CreateWindow("Pong-SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Load(renderer);

	board = Board();
	ball = Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 16, 16, 5, 5,wallBounceSound);
	leftPaddle = Paddle(16, 200, 16, 64, 4);
	rightPaddle = Paddle(SCREEN_WIDTH - 32, 200, 16, 64, 4);
	//Main game loop.
	while (!quit)
	{
		//Check if the player quit.
		quit = HandleInput();

		//Update objects.
		Update(renderer);

		//Draw objects.
		Draw(renderer);

	}

	Close(renderer, window);

	return 0;
}
void Load(SDL_Renderer* renderer)
{
	titleText.Load(renderer, "PONG", { 0xFF,0xFF,0xFF });
	subTitleText.Load(renderer, "By Idan Dvir", { 0xFF,0xFF,0xFF });
	startGameText.Load(renderer, "Start Game", { 0x00,0x00,0x00 });
	quitGameText.Load(renderer, "Quit Game", { 0xFF,0xFF,0xFF });

	playerScoreText.Load(renderer, "0", { 0xFF,0xFF,0xFF });
	opponentScoreText.Load(renderer, "0", { 0xFF,0xFF,0xFF });
	
	gameOverTitleText.Load(renderer, "", { 0xFF,0xFF,0xFF });
	restartGameText.Load(renderer, "Restart Game", { 0x00,0x00,0x00 });
	returnToMenu.Load(renderer, "Return To Menu", { 0xFF,0xFF,0xFF });

	wallBounceSound.Load();
	paddleBounceSound.Load();
	playerGoal.Load();
	opponentGoal.Load();
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
			else if (e.key.keysym.sym == SDLK_s)
			{
				input.MoveDown = true;
			}
			else if (e.key.keysym.sym == SDLK_a)
			{
				input.MoveLeft = true;
			}
			else if (e.key.keysym.sym == SDLK_d) 
			{
				input.MoveRight = true;
			}
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				input.Select = true;
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
			else if (e.key.keysym.sym == SDLK_a)
			{
				input.MoveLeft = false;
			}
			else if (e.key.keysym.sym == SDLK_d)
			{
				input.MoveRight = false;
			}
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				input.Select = false;
			}
		}
		else if (e.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}
void Update(SDL_Renderer* renderer)
{
	if (currentMenu == 0)
	{
		UpdateMainMenu(renderer);
	}
	else if (currentMenu == 1)
	{
		UpdateGameMenu(renderer);
	}
	else if (currentMenu == 2)
	{
		UpdateGameOverMenu(renderer);
	}
}
void UpdateGameMenu(SDL_Renderer* renderer)
{
	ball.Update(SCREEN_HEIGHT);
	leftPaddle.Update(SCREEN_HEIGHT, &input);

	SDL_Rect ballRect = ball.ToRect();
	SDL_Rect paddleRect = leftPaddle.ToRect();
	CheckCollision(&ballRect, &paddleRect, paddleRect.x + paddleRect.w);

	rightPaddle.UpdateAI(SCREEN_HEIGHT, ballRect.y);
	paddleRect = rightPaddle.ToRect();
	CheckCollision(&ballRect, &paddleRect, paddleRect.x - paddleRect.w);

	if (ballRect.x < 0)
	{
		opponentGoal.Play();
		opponentScore++;
		sprintf_s(newText, "%d", opponentScore);
		opponentScoreText.ChangeText(renderer, newText, { 0xFF,0xFF,0xFF });
		ball.ResetPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		if (opponentScore >= 7)
		{
			ball.SetSpeed(0,0);
			gameOverTitleText.ChangeText(renderer, "Defeat...", { 0xFF,0xFF,0xFF });
			currentMenu = 2;
		}
	}
	else if (ballRect.x > SCREEN_WIDTH - ballRect.w)
	{
		playerGoal.Play();
		playerScore++;
		sprintf_s(newText, "%d", playerScore);
		playerScoreText.ChangeText(renderer, newText, { 0xFF,0xFF,0xFF });
		ball.ResetPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		if (playerScore >= 7)
		{
			ball.SetSpeed(0,0);
			gameOverTitleText.ChangeText(renderer, "VICTORY!", { 0xFF,0xFF,0xFF });
			currentMenu = 2;
		}
	}
}
void UpdateMainMenu(SDL_Renderer* renderer)
{
	if (input.MoveLeft)
	{
		currentTextSelect = 0;
		startGameText.ChangeText(renderer, "Start Game", { 0x00,0x00,0x00 });
		quitGameText.ChangeText(renderer, "Quit Game", { 0xFF,0xFF,0xFF });
	}
	else if (input.MoveRight)
	{
		currentTextSelect = 1;
		startGameText.ChangeText(renderer, "Start Game", { 0xFF,0xFF,0xFF });
		quitGameText.ChangeText(renderer, "Quit Game", { 0x00,0x00,0x00 });
	}
	else if (input.Select)
	{
		if (currentTextSelect == 0)
		{
			currentMenu = 1;
			ball.SetSpeed(5,5);
		}
		else if (currentTextSelect == 1)
		{
			quit = true;
		}
	}
}
void UpdateGameOverMenu(SDL_Renderer* renderer)
{
	if (input.MoveLeft)
	{
		currentTextSelect = 0;
		restartGameText.ChangeText(renderer, "Restart Game", { 0x00,0x00,0x00 });
		returnToMenu.ChangeText(renderer, "Return To Menu", { 0xFF,0xFF,0xFF });
	}
	else if (input.MoveRight)
	{
		currentTextSelect = 1;
		restartGameText.ChangeText(renderer, "Restart Game", { 0xFF,0xFF,0xFF });
		returnToMenu.ChangeText(renderer, "Return To Menu", { 0x00,0x00,0x00 });
	}
	else if (input.Select)
	{
		if (currentTextSelect == 0)
		{
			currentMenu = 1;
			ball.SetSpeed(5,5);
			RestartGame(renderer);
		}
		else if (currentTextSelect == 1)
		{
			currentMenu = 0;
			currentTextSelect = 0;
			returnToMenu.ChangeText(renderer, "Return To Menu", { 0xFF,0xFF,0xFF });
			input.Select = false;
		}
	}
}
void RestartGame(SDL_Renderer* renderer)
{
	playerScore = 0;
	opponentScore = 0;
	playerScoreText.Load(renderer, "0", { 0xFF,0xFF,0xFF });
	opponentScoreText.Load(renderer, "0", { 0xFF,0xFF,0xFF });
}
inline void CheckCollision(SDL_Rect* ballRect, SDL_Rect* paddleRect, int ballNewX)
{
	bool colliding = Collision::AABBCollision(ballRect, paddleRect);
	
	
	if (colliding)
	{
		paddleBounceSound.Play();
		double ballAngle;
		double hypoDistance;
		double oppoDistance;
		if (paddleRect->x > SCREEN_WIDTH / 2)
		{
			hypoDistance = Triangle::CalculateDistance((double)ballRect->x + ballRect->w / 2, (double)ballRect->y + ballRect->h / 2
				, (double)paddleRect->x + paddleRect->w / 2, (double)paddleRect->y + paddleRect->h / 2);
			oppoDistance = Triangle::CalculateDistance((double)paddleRect->x + paddleRect->w / 2, (double)ballRect->y + ballRect->h / 2
				, (double)paddleRect->x + paddleRect->w / 2, (double)paddleRect->y + paddleRect->h / 2);
			ballAngle = Triangle::GetSinAngle(hypoDistance, oppoDistance);
		}
		else
		{
			hypoDistance = Triangle::CalculateDistance((double)ballRect->x + ballRect->w / 2, (double)ballRect->y + ballRect->h / 2
				, (double)paddleRect->x + paddleRect->w / 2, (double)paddleRect->y + paddleRect->h / 2);
		    oppoDistance = Triangle::CalculateDistance((double)paddleRect->x + paddleRect->w / 2, (double)ballRect->y + ballRect->h / 2
				, (double)paddleRect->x + paddleRect->w / 2, (double)paddleRect->y + paddleRect->h / 2);
		    ballAngle = Triangle::GetSinAngle(hypoDistance, oppoDistance);
		}
		double remmapedAngle = RemapValue(ballAngle, 50.0, 75.0, 0.5, 1.5);
		if (ballRect->y + ballRect->h / 2 < paddleRect->y + paddleRect->h / 2)
		{
			remmapedAngle = -remmapedAngle;
		}
		ball.SetSpeed(ball.GetXSpeed() , 5.0 * remmapedAngle);
		ball.HorizontalBounce(ballNewX);
	}
}
void Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	if (currentMenu == 0)
	{
		titleText.Draw(renderer);
		subTitleText.Draw(renderer);
		SDL_Rect rect;
		if (currentTextSelect == 0)
		{
			rect = startGameText.ToRect();
		}
		else if (currentTextSelect == 1)
		{
			rect = quitGameText.ToRect();
		}
		rect.x -= rect.w / 8 / 2;
		rect.y -= rect.h / 24/2;
		rect.w += rect.w / 8;
		rect.h += rect.h / 24;

		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xA0);
		SDL_RenderFillRect(renderer, &rect);

		startGameText.Draw(renderer);
		quitGameText.Draw(renderer);
	}
	else if (currentMenu == 1)
	{		
		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xA0);
		board.Draw(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		playerScoreText.Draw(renderer);
		opponentScoreText.Draw(renderer);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		ball.Draw(renderer);
		leftPaddle.Draw(renderer);
		rightPaddle.Draw(renderer);
	}
	else if (currentMenu == 2)
	{
		gameOverTitleText.Draw(renderer);
		SDL_Rect rect;
		if (currentTextSelect == 0)
		{
			rect = restartGameText.ToRect();
		}
		else if (currentTextSelect == 1)
		{
			rect = returnToMenu.ToRect();
		}
		rect.x -= rect.w / 8 / 2;
		rect.y -= rect.h / 24 / 2;
		rect.w += rect.w / 8;
		rect.h += rect.h / 24;

		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xA0);
		SDL_RenderFillRect(renderer, &rect);

		restartGameText.Draw(renderer);
		returnToMenu.Draw(renderer);
	}
	SDL_RenderPresent(renderer);
}
void Close(SDL_Renderer* renderer,SDL_Window* window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
}
inline double RemapValue(double value, double low1, double high1, double low2, double high2)
{
	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}