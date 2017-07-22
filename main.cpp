#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>

using namespace std;

//g++ main.cpp -IC:\Development\SDL2_MinGW_32Bit\include\SDL2 -IC:\Development\SDL2Image_MinGW_32Bits\include\SDL2 -LC:\Development\SDL2_MinGW_32Bit\lib -LC:\Development\SDL2Image_MinGW_32Bits\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -o SDL_Game

//Defines max size
const int maxSize = 10;

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

//Player speed (-1 or 0 or 1)  in x and y
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
	
	gWindow = SDL_CreateWindow("Cobrinha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (gWindow == NULL) {		
		printf("Could not create window : %s\n", SDL_GetError());		
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);
}

void UpdateGameScreen(position pPos[maxSize], SDL_Rect fPos, int size) {	

	SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));

	//Player rect in screen
	SDL_Rect targetRect;
	targetRect.w = 20;
	targetRect.h = 20;

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
	pSpeed.x = 1;
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

	
	while (!quit) {
		if (SDL_PollEvent(&e)) {

			if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) {

				quit = true;

			} else if (getInput) {

				if (e.key.keysym.sym == SDLK_RIGHT && pSpeed.x == 0) {

					pSpeed.x = 1;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_LEFT && pSpeed.x == 0) {

					pSpeed.x = -1;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_UP && pSpeed.y == 0) {

					pSpeed.x = 0;
					pSpeed.y = -1;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_DOWN && pSpeed.y == 0) {

					pSpeed.x = 0;
					pSpeed.y = 1;
					getInput = false;

				}
			}			
		}

		endTime = SDL_GetTicks();

		/*

		Terminar de ajeitar essa parte depois
		NAO ESQUECA
		OLHE ISSO
		AQUI
		AQUI
		AQUI

		if (endTime - startTime >= 500) {

			nextFront = inFront - 1;			

			if (nextFront == -1) {
				nextFront = pSize - 1;
			}

			newPos.x = targetPos[inFront].x + pSpeed.x * 20;
			newPos.y = targetPos[inFront].y + pSpeed.y * 20;


			if (newPos.x == foodPos.x && newPos.y == foodPos.y) {
				foodPos.x += 60;
				foodPos.y += 40;

				pSize++;

				orderedPos[0].x = newPos.x;
				orderedPos[0].y = newPos.y;

				orderedPos[pSize - 1].x = targetPos[nextFront].x;
				orderedPos[pSize - 1].y = targetPos[nextFront].y;
				nextToSave = inFront;

				for (int i = 1; i < pSize - 1; i++) {
					orderedPos[i].x = targetPos[nextToSave].x;
					orderedPos[i].y = targetPos[nextToSave].y;

					nextToSave++;

					if (nextToSave == pSize - 1) {
						nextToSave == 0;
					}
				}


				for (int i = 0; i < pSize - 1; i++) {
					targetPos[i].x = orderedPos[i].x;
					targetPos[i].y = orderedPos[i].y;

					nextToSave++;

					if (nextToSave == pSize - 1) {
						nextToSave == 0;
					}
				}

				inFront = 0;
				nextFront = inFront;				

			} else {
				targetPos[nextFront].x = newPos.x;
				targetPos[nextFront].y = newPos.y;
				inFront = nextFront;
			}

			getInput = true;
			startTime = SDL_GetTicks();
		}

		*/

		UpdateGameScreen(playerPos, foodPos, pSize);
	}

    EndAll();    
	return 0;
}



