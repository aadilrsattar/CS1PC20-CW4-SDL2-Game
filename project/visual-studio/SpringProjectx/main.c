/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"
#include <Windows.h>
static void capFrameRate(long* then, float* remainder);


char* global_dir = "C:\\Users\\di918039\\source\\repos\\cs1pr-portfolio\\project-visual-studio\\SpringProject";

int WinMain() {
	long then;
	float remainder;

	memset(&app, 0, sizeof(App));

	app.textureTail = &app.textureHead;

	initSDL();

	atexit(cleanup);

	initGame();

	initStage();

	then = SDL_GetTicks();

	remainder = 0;
	
	SDL_Texture* playButton;
	playButton = loadTexture("gfx/menu/PLAY.png");
	SDL_Texture* pizza;
	pizza = loadTexture("gfx/hotdog.png");
	SDL_Texture* mapButton;
	mapButton = loadTexture("gfx/menu/Map_Select.png");
	SDL_Texture* exitButton;
	exitButton = loadTexture("gfx/menu/EXIT.png"); //loads all the textures needed for the menu

	SDL_Rect button1;
	button1.w = 156;
	button1.h = 40;
	button1.x = (SCREEN_WIDTH - 156) / 2;
	button1.y = (SCREEN_HEIGHT) / 2 - 24;
	SDL_Rect button2;
	button2.w = 156;
	button2.h = 40;
	button2.x = (SCREEN_WIDTH - 156) / 2;
	button2.y = (SCREEN_HEIGHT) / 2 + 54;
	SDL_Rect exit_button;
	exit_button.w = 156;
	exit_button.h = 40;
	exit_button.x = (SCREEN_WIDTH-156) / 2;
	exit_button.y = (SCREEN_HEIGHT) / 2 + 132; //this allows to click on the buttons on the locations they are on the screen


	while (1)
	{
		SDL_SetRenderDrawColor(app.renderer, 220, 20, 60, 0);
		SDL_ShowCursor(1);
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 20, 20, 20, TEXT_CENTER, "AADIL'S HOTDOG MANIA");
		SDL_Event e;
		SDL_Point mouse;

		while (SDL_PollEvent(&e) && app.state != 1)
		{
			if (e.type == SDL_MOUSEMOTION)
			{
				mouse.x = e.motion.x;
				mouse.y = e.motion.y;
				break;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (SDL_PointInRect(&mouse, &button1)) {
					app.state = 1;
					stage.pizzaFound = 0;
					initStage();
					SDL_ShowCursor(0);
				}
				if (SDL_PointInRect(&mouse, &button2)) {
					app.state = 2;
				}
				if (SDL_PointInRect(&mouse, &exit_button)) {
					SDL_Quit();
					exit(0);
					return 0;
				}
				break;											//this checks if the user presses down on the buttons while over this button
			}
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				return 0;
				break;
			}
		}
		if (SDL_PointInRect(&mouse, &button1)) {
			SDL_SetTextureColorMod(playButton, 150, 150, 150);			//while the user is hovering over the buttons, it is a different shade

		}
		else if (SDL_PointInRect(&mouse, &button2)) {
			SDL_SetTextureColorMod(mapButton, 150, 150, 150);

		}
		else if (SDL_PointInRect(&mouse, &exit_button)) {
			SDL_SetTextureColorMod(exitButton, 150, 150, 150);
		}
		else {
			SDL_SetTextureColorMod(playButton, 255, 255, 255);
			SDL_SetTextureColorMod(mapButton, 255, 255, 255);
			SDL_SetTextureColorMod(exitButton, 255, 255, 255);
																	//this sets the normal colours of the buttons

		}
		blit(playButton, (SCREEN_WIDTH - 156) / 2, (SCREEN_HEIGHT / 2) - 24, 0);
		blit(pizza, (SCREEN_WIDTH - 31) / 2, 100, 0);
		blit(mapButton, (SCREEN_WIDTH - 156) / 2, (SCREEN_HEIGHT / 2) + 54, 0);
		blit(exitButton, (SCREEN_WIDTH - 156) / 2, (SCREEN_HEIGHT / 2) + 132, 0);

		while (app.state == 1)
		{
			prepareScene();
			doInput();

			app.delegate.logic();
			app.delegate.draw();
			
			// this allows for a timer to run on the code 
			if (timeron == 0){
				ms++;
				if (ms >= 60) {
					sec++;
					ms = 0;
				}
				if (sec >= 60) {
					min++;
					sec = 0;
				}				
			}

			presentScene();

			capFrameRate(&then, &remainder);
		}

		while (app.state == 2)
		{
			prepareScene();

			SDL_Texture* easybutton;  
			easybutton = loadTexture("gfx/menu/EASY.png");
			SDL_Texture* hardbutton;  
			hardbutton = loadTexture("gfx/menu/HARD.png"); //load the easy and hard load buttons

			SDL_SetRenderDrawColor(app.renderer, 255, 128, 0, 0);
			SDL_RenderClear(app.renderer);

			drawText(530, 150, 25, 25, 25, TEXT_LEFT, "MAP SELECT");

			SDL_Rect easy;
			easy.w = 156;
			easy.h = 40;
			easy.x = (SCREEN_WIDTH - 156) / 2;
			easy.y = (SCREEN_HEIGHT) / 2 - 24;

			SDL_Rect hard;
			hard.w = 156;
			hard.h = 40;
			hard.x = (SCREEN_WIDTH - 156) / 2;
			hard.y = (SCREEN_HEIGHT) / 2 + 54;



			while (SDL_PollEvent(&e) && app.state != 1)
			{
				if (e.type == SDL_MOUSEMOTION)
				{
					mouse.x = e.motion.x;
					mouse.y = e.motion.y;
					break;
				}

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					if (SDL_PointInRect(&mouse, &easy)) {
						app.map_selection = 0;
						app.state = 0;

					}
					if (SDL_PointInRect(&mouse, &hard)) {
						app.map_selection = 1;
						app.state = 0;

					}
					if (SDL_PointInRect(&mouse, &exit_button)) {
						app.state = 0;
					}
					break;
				}

				if (e.type == SDL_QUIT)
				{
					SDL_Quit();
					return 0;
					break;
				}
			}
			if (SDL_PointInRect(&mouse, &easy)) {
				SDL_SetTextureColorMod(easybutton, 100, 100, 100);
			}
			else if (SDL_PointInRect(&mouse, &hard)) {
				SDL_SetTextureColorMod(hardbutton, 100, 100, 100);
			}
			else if (SDL_PointInRect(&mouse, &exit_button)) {
				SDL_SetTextureColorMod(exitButton, 100, 100, 100);
			}
			else {
				SDL_SetTextureColorMod(easybutton, 255, 255, 255);
				SDL_SetTextureColorMod(hardbutton, 255, 255, 255);
				SDL_SetTextureColorMod(exitButton, 255, 255, 255);

			}
			blit(easybutton, (SCREEN_WIDTH - 156) / 2, (SCREEN_HEIGHT / 2) - 24, 0);
			blit(hardbutton, (SCREEN_WIDTH - 156) / 2, (SCREEN_HEIGHT / 2) + 54, 0);
			blit(exitButton, (SCREEN_WIDTH - 156) / 2, (SCREEN_HEIGHT / 2) + 132, 0);
			presentScene();

			capFrameRate(&then, &remainder);

		}
		presentScene();
		SDL_RenderClear(app.renderer);
	}

}

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)* remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
