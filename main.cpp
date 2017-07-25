#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_Mixer.h>
#include <time.h>

using namespace std;

//Audio that plays on item get
Mix_Chunk *AudioItem = NULL;
//Audio played on death
Mix_Chunk *AudioDeath = NULL;


//Map                                          0 == Non-Wall Space      1 == Wall
const int Map[30][40] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//Defines max size
const int maxSize = 70;

//Defines time per ScreenUpdate in miliseconds
const int upTime = 100;

//Define Window sizes
const int WINDOW_SIZE_X = 1000, WINDOW_SIZE_Y = 600;

//Checks if snake will crash
bool willCrash = false;

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

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, AUDIO_S16, 2, 512);
	
	gWindow = SDL_CreateWindow("Cobrinha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_OPENGL);

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	//Random seed for rand() function
	srand (time(NULL));
}

void UpdateGameScreen(position pPos[], SDL_Rect fPos, int size) {	

	//Player rect in screen
	SDL_Rect playerRect;
	playerRect.w = 20;
	playerRect.h = 20;

	SDL_Rect wallRect;
	wallRect.w = 20;
	wallRect.h = 20;

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

		
	//Paints Wall on screen
	for (int i = 0; i < 30; i++) {

		for (int k = 0; k < 40; k++) {

			if (Map[i][k] == 1) {
				wallRect.x = k * 20;
				wallRect.y = i * 20;

				SDL_BlitSurface(wallImage, NULL, gScreenSurface, &wallRect);
			}
		}
	}

	//Paints Player on screen
	for (int i = 0; i < size; i++) {
		
		playerRect.x = pPos[i].x;
		playerRect.y = pPos[i].y;					

		SDL_BlitSurface(pImage, NULL, gScreenSurface, &playerRect);
	}

	//Paints Food on screen
	SDL_BlitSurface(foodImage, NULL, gScreenSurface, &fPos);	
	//Updates Screen
	SDL_UpdateWindowSurface(gWindow);

}

SDL_Rect FoodRandomizer(SDL_Rect f, position player[], int size) {

	bool isPosFree = false;

	while (!isPosFree) {

		isPosFree = true;

		f.x = rand() % 780 + 1;
		f.y = rand() % 580 + 1;

		f.x -= (f.x % 40);
		f.y -= (f.y % 40);

		//Checks if there is a player on next position
		for (int i = 0; i < size; i++) {

			if ((f.x == player[i].x && f.y == player[i].y)) {
				isPosFree = false;			
			}
		}
		//Check if there is a wall on the next position		
		if (Map[f.y / 20][f.x /20] == 1) {
			isPosFree = false;
		}
	}

	return f;
}


void EndAll() {

	//Destroy Window
	SDL_DestroyWindow(gWindow);

	Mix_CloseAudio();

	//Clean up subsystems
	SDL_Quit();

}

int main(int argc, char* agrs[]) {

    Initialize();

    //References Audio
    AudioItem = Mix_LoadWAV("Assets/Audio/itemgetaudio.wav");
    AudioDeath = Mix_LoadWAV("Assets/Audio/audiodeath.wav");

    //Snake Size
    int pSize = 3, inFront = 0, nextFront, nextToSave;

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
	playerPos[0].x = 400;
	playerPos[0].y = 300;
	playerPos[1].x = 400;
	playerPos[1].y = 300;
	playerPos[2].x = 400;
	playerPos[2].y = 300;

	//Zero all other pieces position
	for (int i = 3; i < maxSize; i++)	{

		playerPos[i].x = 0;
		playerPos[i].y = 0;

	}

	//Where food will appear
	SDL_Rect foodPos;
	foodPos.x = 80;
	foodPos.y = 0;
	foodPos.w = 20;
	foodPos.h = 20;

	//Ramdomize food position concerning walls and player positions
	foodPos = FoodRandomizer(foodPos, playerPos, pSize);

	//Time Handler  --  SDL_GetTicks() gets the miliseconds passed since Init
	int startTime = SDL_GetTicks(), endTime;
	
	UpdateGameScreen(playerPos, foodPos, pSize);

	
	while (!quit && pSize != maxSize) {
		while (SDL_PollEvent(&e)) {

			//Checks if player clicked on X or pushed Esc
			if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT) {
				quit = true;

			} else if (getInput) {

				if (e.key.keysym.sym == SDLK_RIGHT && pSpeed.x == 0 && e.type == SDL_KEYDOWN) {

					pSpeed.x = 20;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_LEFT && pSpeed.x == 0 && e.type == SDL_KEYDOWN) {

					pSpeed.x = -20;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_UP && pSpeed.y == 0 && e.type == SDL_KEYDOWN) {

					pSpeed.x = 0;
					pSpeed.y = -20;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_DOWN && pSpeed.y == 0 && e.type == SDL_KEYDOWN) {

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


			//If food is in the next place that snake will go...
			if (newPos.x == foodPos.x && newPos.y == foodPos.y) {

				Mix_PlayChannel(-1, AudioItem, 0);

				foodPos.x = -60;
				foodPos.y = 0;	

				int changePos = inFront;

				for (int i = 0; i < pSize + 1; i++) {

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

				//Ramdomize food position concerning walls and player positions
				foodPos = FoodRandomizer(foodPos, playerPos, pSize);				

			} else {

				//Checks for snake part on next position
				for (int i = 0; i < pSize; i++) {

					if (i != nextFront) {
						if (playerPos[i].x == newPos.x && playerPos[i].y == newPos.y) {
							willCrash = true;
							Mix_PlayChannel(-1, AudioDeath, 0);
						}
					}
				}

				if (!willCrash) {
					
					//Checks for block in next position
					if (Map[newPos.y / 20][newPos.x / 20] == 1) {

						willCrash = true;
						Mix_PlayChannel(-1, AudioDeath, 0);
				
					} else {

						playerPos[nextFront].x = newPos.x;
						playerPos[nextFront].y = newPos.y;
						
						inFront = nextFront;
						
						startTime = SDL_GetTicks();

						getInput = true;

					}
				}
			}
			
		}	

		while (willCrash && !quit) {

			while (SDL_PollEvent(&e)) {

				if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT) {

					quit = true;

				} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
					
					pSize = 3;					

			 		playerPos[0].x = 400;
					playerPos[0].y = 300;
					playerPos[1].x = 400;
					playerPos[1].y = 300;
					playerPos[2].x = 400;
					playerPos[2].y = 300;

					for (int i = 3; i < maxSize; i++) {
						playerPos[i].x = 0;
						playerPos[i].y = 0;
				 	}

				 	//Ramdomize food position concerning walls and player positions
					foodPos = FoodRandomizer(foodPos, playerPos, pSize);

					pSpeed.x = 20;
					pSpeed.y = 0;

				 	//startTime = SDL_GetTicks();
					willCrash = false;				

				}
			}

			getInput = false;
		}		

		UpdateGameScreen(playerPos, foodPos, pSize);
	}

    EndAll();        
    return 0;
}


