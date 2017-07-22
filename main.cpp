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

void UpdateGameScreen(SDL_Rect target) {

	SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 255, 255, 255));

	SDL_BlitSurface(pImage, NULL, gScreenSurface, &target);	

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

    //Event Handler
	SDL_Event e;
	//Check if player wants to quit from game
	bool quit = false;

	//Player position in window
	SDL_Rect playerPos;
    playerPos.x = 400;
	playerPos.y = 300;
	playerPos.w = 20;
	playerPos.h = 20;

	//Player initial speed		
	speed pSpeed;
	pSpeed.x = 1;
	pSpeed.y = 0;

	//Time Handler
	int startTime, endTime;

	startTime = SDL_GetTicks();

	UpdateGameScreen(playerPos);

	while (!quit) {
		if (SDL_PollEvent(&e)) {

			if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) {

				quit = true;

			} else {

				if (e.key.keysym.sym == SDLK_RIGHT && pSpeed.x == 0) {

					pSpeed.x = 1;
					pSpeed.y = 0;

				} else if (e.key.keysym.sym == SDLK_LEFT && pSpeed.x == 0) {

					pSpeed.x = -1;
					pSpeed.y = 0;

				} else if (e.key.keysym.sym == SDLK_UP && pSpeed.y == 0) {

					pSpeed.x = 0;
					pSpeed.y = -1;

				} else if (e.key.keysym.sym == SDLK_DOWN && pSpeed.y == 0) {

					pSpeed.x = 0;
					pSpeed.y = 1;

				}
			}			
		}

		endTime = SDL_GetTicks();

		if (endTime - startTime >= 1000) {

			playerPos.x += pSpeed.x * 20;
			playerPos.y += pSpeed.y * 20; 

			startTime = SDL_GetTicks();
		}

		UpdateGameScreen(playerPos);

	}

    EndAll();    
	return 0;
}



