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

static SDL_Texture* pete[2];
static SDL_Texture* peteL[6];
static SDL_Texture* peteR[6]; //creates each of the arrays for the animations

int left = 0;
int right = 0;
int direct = 0;	//values needed for animations

int Maxjump = 2;

void initPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;

	player->health = 1;

	pete[0] = loadTexture("gfx/animation/idle_right.png"); //load textures for animations
	pete[1] = loadTexture("gfx/animation/idle_left.png");

	peteR[0] = loadTexture("gfx/animation/walk_right1.png");
	peteR[1] = loadTexture("gfx/animation/walk_right2.png");
	peteR[2] = loadTexture("gfx/animation/walk_right3.png");
	peteR[3] = loadTexture("gfx/animation/walk_right4.png");
	peteR[4] = loadTexture("gfx/animation/walk_right5.png");
	peteR[5] = loadTexture("gfx/animation/walk_right6.png");

	peteL[0] = loadTexture("gfx/animation/walk_left1.png");
	peteL[1] = loadTexture("gfx/animation/walk_left2.png");
	peteL[2] = loadTexture("gfx/animation/walk_left3.png");
	peteL[3] = loadTexture("gfx/animation/walk_left4.png");
	peteL[4] = loadTexture("gfx/animation/walk_left5.png");
	peteL[5] = loadTexture("gfx/animation/walk_left6.png"); 

	player->texture = pete[0];

	SDL_QueryTexture(player->texture, 0, NULL, &player->w, &player->h);
}

void doPlayer(void)
{
	player->dx = 0;

	if (player->isOnGround) {
		player->Jump = 0;
		player->texture = pete[direct];

	}
	if (app.keyboard[SDL_SCANCODE_A] || app.keyboard[SDL_SCANCODE_LEFT]) // added or left so that more accessibility
	{
		player->dx = -PLAYER_MOVE_SPEED;
		direct = 1;
		if (player->isOnGround) {
			left = (left + 1) % 24;
			player->texture = peteL[left / 6]; //this changes the values repeatedly, so that the character appears to be animated
		}
	}
	if (app.keyboard[SDL_SCANCODE_D] || app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_MOVE_SPEED;
		direct = 0;
		if (player->isOnGround) {
			right = (right + 1) % 24;
			player->texture = peteR[right / 6];
		}

	}

	if ((app.keyboard[SDL_SCANCODE_SPACE] || app.keyboard[SDL_SCANCODE_UP]) && (player->Jump < Maxjump)) 
	{
		app.keyboard[SDL_SCANCODE_SPACE] = 0;
		app.keyboard[SDL_SCANCODE_UP] = 0;

		player->riding = NULL;

		player->dy = -20;

		playSound(SND_JUMP, CH_PLAYER); // allows for double jump function
	}

	if (app.keyboard[SDL_SCANCODE_L] && player->isOnGround) { // this function speeds up my character

		if (app.keyboard[SDL_SCANCODE_A] || app.keyboard[SDL_SCANCODE_LEFT])
		{
			player->dx = -PLAYER_MOVE_SPEED*1.5;
			direct = 1;
			if (player->isOnGround) {
				left = (left + 3) % 24;
				player->texture = peteL[left / 6];//the animations are also faster
			}
		}
		if (app.keyboard[SDL_SCANCODE_D] || app.keyboard[SDL_SCANCODE_RIGHT])
		{
			player->dx = PLAYER_MOVE_SPEED*1.5;
			direct = 0;
			if (player->isOnGround) {
				right = (right + 3) % 24;
				player->texture = peteR[right / 6];
			}
		}
	}

	if (app.keyboard[SDL_SCANCODE_I])
	{
		player->x = player->y = 0;

		app.keyboard[SDL_SCANCODE_I] = 0; //changed space to I as it was more user friendly
	}
	if (app.keyboard[SDL_SCANCODE_ESCAPE]) {
		SDL_Quit();
		timeron = 0; ms = 0; sec = 0; min = 0;//resets timer function
		WinMain(); // escapes the game and goes back to main menu

	}
}