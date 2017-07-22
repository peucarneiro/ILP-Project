#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>

using namespace std;

//g++ main.cpp -IC:\Development\SDL2_MinGW_32Bit\include\SDL2 -IC:\Development\SDL2Image_MinGW_32Bits\include\SDL2 -LC:\Development\SDL2_MinGW_32Bit\lib -LC:\Development\SDL2Image_MinGW_32Bits\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -o SDL_Game



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

void Initialize() {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	
	gWindow = SDL_CreateWindow("Cobrinha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (gWindow == NULL) {		
		printf("Could not create window : %s\n", SDL_GetError());		
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);
}

void UpdateGameScreen(SDL_Rect pPos[10], SDL_Rect fPos, int size) {

	SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));


	for (int i = 0; i < size; i++) {
		
		SDL_BlitSurface(pImage, NULL, gScreenSurface, &pPos[i]);

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

	//Player position in window
	SDL_Rect playerPos[10];
    playerPos[0].x = 200;
	playerPos[0].y = 100;
	playerPos[0].w = 20;
	playerPos[0].h = 20;

	for (int i = 1; i < 10; i++) {

		playerPos[i].x = 0;
		playerPos[i].y = 0;
		playerPos[i].w = 20;
		playerPos[i].h = 20;

	}

	//Player initial speed		
	speed pSpeed;
	pSpeed.x = 1;
	pSpeed.y = 0;

	speed newPos;

	speed PosSave[10];

	SDL_Rect foodPos;
	foodPos.x = 80;
	foodPos.y = 0;
	foodPos.w = 20;
	foodPos.h = 20;


	//Time Handler
	int startTime, endTime;

	startTime = SDL_GetTicks();

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

		if (endTime - startTime >= 500) {

			nextFront = inFront - 1;			

			if (nextFront == -1) {
				nextFront = pSize - 1;
			}

			newPos.x = playerPos[inFront].x + pSpeed.x * 20;
			newPos.y = playerPos[inFront].y + pSpeed.y * 20;


			if (newPos.x == foodPos.x && newPos.y == foodPos.y) {
				foodPos.x += 60;
				foodPos.y += 40;

				pSize++;

				PosSave[0].x = newPos.x;
				PosSave[0].y = newPos.y;

				PosSave[pSize - 1].x = playerPos[nextFront].x;
				PosSave[pSize - 1].y = playerPos[nextFront].y;
				nextToSave = inFront;

				for (int i = 1; i < pSize - 1; i++) {
					PosSave[i].x = playerPos[nextToSave].x;
					PosSave[i].y = playerPos[nextToSave].y;

					nextToSave++;

					if (nextToSave == pSize - 1) {
						nextToSave == 0;
					}
				}


				for (int i = 0; i < pSize - 1; i++) {
					playerPos[i].x = PosSave[i].x;
					playerPos[i].y = PosSave[i].y;

					nextToSave++;

					if (nextToSave == pSize - 1) {
						nextToSave == 0;
					}
				}

				inFront = 0;
				nextFront = inFront;				

			} else {
				playerPos[nextFront].x = newPos.x;
				playerPos[nextFront].y = newPos.y;
				inFront = nextFront;
			}


			getInput = true;
			startTime = SDL_GetTicks();
		}

		UpdateGameScreen(playerPos, foodPos, pSize);
	}

    EndAll();    
	return 0;
}



