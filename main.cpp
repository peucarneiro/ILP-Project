#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <time.h>

using namespace std;

/*
Use this code to complile (only on my PC though...) :

g++ main.cpp -IC:\Development\SDL2_MinGW_32Bit\include\SDL2 -IC:\Development\SDL2Image_MinGW_32Bits\include\SDL2 -LC:\Development\SDL2_MinGW_32Bit\lib -LC:\Development\SDL2Image_MinGW_32Bits\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -o SDL_Game

*/

//Defines max size
const int maxSize = 70;

//Defines time per ScreenUpdate in miliseconds
const int upTime = 100;

//Define Window sizes
const int WINDOW_SIZE_X = 1000, WINDOW_SIZE_Y = 600;

//Checks if snake will crash
bool willCrash = false;
//Checks if new food pos is OK
bool isPosOk = false;

//Window
SDL_Window* gWindow = NULL;

//Surface in Screen
SDL_Surface* gScreenSurface = NULL;	
//Player image (Cobrinha)
SDL_Surface* pImage = IMG_Load("Assets/Art/player.png");
//Food Image
SDL_Surface* foodImage = IMG_Load("Assets/Art/food.png");
//Wall Image
SDL_Surface* wallImage = IMG_Load("Assets/Art/wall.png");

//Player speed (-20 or 0 or 20)  in x and y
typedef struct {
	int x;
	int y;
} speed;

//Player position x and y
typedef struct {
	int x;
	int y;
} position;

void Initialize() {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	
	gWindow = SDL_CreateWindow("Cobrinha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_OPENGL);
	if (gWindow == NULL) {		
		printf("Could not create window : %s\n", SDL_GetError());		
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	//Random seed
	srand (time(NULL));
}

void UpdateGameScreen(position pPos[maxSize], SDL_Rect fPos, int size) {	

	//Player rect in screen
	SDL_Rect targetRect;
	targetRect.w = 20;
	targetRect.h = 20;

	//Difine Rect to paint black and white (for now)
	SDL_Rect blackRect, whiteRect;
	blackRect.x = 0;
	blackRect.y = 0;
	blackRect.w = 800;
	blackRect.h = 600;
	whiteRect.x = 800;
	whiteRect.y = 0;	
	whiteRect.w = WINDOW_SIZE_X - 800;
	whiteRect.h = 600;

	//Paints game background
	SDL_FillRect(gScreenSurface, &blackRect, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
	//Paints score menu background
	SDL_FillRect(gScreenSurface, &whiteRect, SDL_MapRGB(gScreenSurface->format, 255, 255, 255));
	
	for (int i = 0; i < size; i++) {
		
		targetRect.x = pPos[i].x;
		targetRect.y = pPos[i].y;

		SDL_BlitSurface(pImage, NULL, gScreenSurface, &targetRect);
	}


	SDL_BlitSurface(foodImage, NULL, gScreenSurface, &fPos);	

	SDL_UpdateWindowSurface(gWindow);

}

void EndAll() {

	//Destroy Window
	SDL_DestroyWindow(gWindow);

	//Clean up subsystems
	SDL_Quit();

}

void ChangeFood() {

}


int main(int argc, char* agrs[]) {

    Initialize();

    //Snake Size
    int pSize = 1, inFront = 0, nextFront, nextToSave;

    //Event Handler
	SDL_Event e;
	//Check if player wants to quit from game
	bool quit = false, getInput = true;

	//Player initial speed		
	speed pSpeed;
	pSpeed.x = 20;
	pSpeed.y = 0;

	//Get the position of where the player will move to
	position newPos;
	//Rearange player positions
	position orderedPos[maxSize];
	//Player positions
	position playerPos[maxSize];
	//First piece of player pos
	playerPos[0].x = 100;
	playerPos[0].y = 100;

	//Zero all other pieces position
	for (int i = 1; i < pSize; i++)	{

		playerPos[i].x = 0;
		playerPos[i].y = 0;

	}

	//Where food will appear
	SDL_Rect foodPos;
	foodPos.x = 80;
	foodPos.y = 0;
	foodPos.w = 20;
	foodPos.h = 20;

	//Time Handler  --  SDL_GetTicks() gets the miliseconds passed since Init
	int startTime = SDL_GetTicks(), endTime;
	
	UpdateGameScreen(playerPos, foodPos, pSize);

	
	while (!quit && pSize != maxSize) {
		if (SDL_PollEvent(&e)) {

			if (e.key.keysym.sym == SDLK_ESCAPE) {

				quit = true;

			} else if (getInput) {

				if (e.key.keysym.sym == SDLK_RIGHT && pSpeed.x == 0) {

					pSpeed.x = 20;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_LEFT && pSpeed.x == 0) {

					pSpeed.x = -20;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_UP && pSpeed.y == 0) {

					pSpeed.x = 0;
					pSpeed.y = -20;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_DOWN && pSpeed.y == 0) {

					pSpeed.x = 0;
					pSpeed.y = 20;
					getInput = false;

				}
			}			
		}

		endTime = SDL_GetTicks();

		if (endTime - startTime >= upTime - (pSize)) {

			nextFront = inFront - 1;			

			if (nextFront == -1) {
				nextFront = pSize - 1;
			}

			newPos.x = playerPos[inFront].x + pSpeed.x;
			newPos.y = playerPos[inFront].y + pSpeed.y;

			if (newPos.x == -20) {
				newPos.x = 780;
			}
			else if (newPos.x == 800) {
				newPos.x = 0;
			}
			else if (newPos.y == -20) {
				newPos.y = 580;
			}
			else if (newPos.y == 600) {
 				newPos.y = 0;
			}


			if (newPos.x == foodPos.x && newPos.y == foodPos.y) {

				foodPos.x = -60;
				foodPos.y = 0;	

				int changePos = inFront;

				orderedPos[0] = newPos;

				for (int i = 1; i < pSize + 1; i++) {

					orderedPos[i] = playerPos[changePos];

					changePos++;

					if (changePos == pSize) {
						changePos = 0;
					}
				}

				//New tail becomes old tail
				playerPos[pSize] = playerPos[nextFront];

				for (int i = 0; i < pSize + 1; i++) {
					playerPos[i] = orderedPos[i];
				}

				pSize++;

				inFront = 0;

				while (!isPosOk) {
					isPosOk = true;

					foodPos.x = rand() % 780 + 1;
					foodPos.y = rand() % 580 + 1;

					foodPos.x -= (foodPos.x % 40);
					foodPos.y -= (foodPos.y % 40);

					for (int i = 0; i < pSize; i++) {

						if (foodPos.x == playerPos[i].x && foodPos.y == playerPos[i].y) {
							isPosOk = false;			
						}
					}
				}

			} else {

				for (int i = 0; i < pSize; i++) {

					if (i != nextFront) {
						if (playerPos[i].x == newPos.x && playerPos[i].y == newPos.y) {
							willCrash = true;
							cout << "PERDEU! APERTE ENTER PARA REINICIAR!" << endl;
						}
					}
				}

				if (!willCrash) {
					
					playerPos[nextFront].x = newPos.x;
					playerPos[nextFront].y = newPos.y;
					
					inFront = nextFront;
					
					startTime = SDL_GetTicks();

					getInput = true;
				}
			}
			
		}	

		while (willCrash && !quit) {

			if (SDL_PollEvent(&e)) {

				if (e.key.keysym.sym == SDLK_ESCAPE) {

					quit = true;

				}			

				if (e.key.keysym.sym == SDLK_RETURN) {
					pSize = 1;

					for (int i = 0; i < maxSize; i++) {
						playerPos[i].x = 100;
						playerPos[i].y = 100;
				 	}

				 	startTime = SDL_GetTicks();
					willCrash = false;
				}
			}
		}	

		isPosOk = false;

		UpdateGameScreen(playerPos, foodPos, pSize);
	}

    EndAll();    
	return 0;
}



