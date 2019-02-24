#include "wolf.h"

int		sdl_render(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e)
{
	SDL_LockSurface(e->surface);
	DrawScreen(e);
	SDL_UnlockSurface(e->surface);
	if (texture == NULL)
		texture = SDL_CreateTextureFromSurface(renderer, e->surface);
	else
	{
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, e->surface);
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	return (1);
}

int		sdl_loop(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e)
{
	
	int				wsad[4] = {0,0,0,0};
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
	float           yaw;
	float           eyeheight;

	yaw = 0;
	eyeheight = 0;
	ground = 0;
	falling = 1;
	moving = 0;
	ducking = 0;

	while (1)
	{
		sdl_render(texture, renderer, e);

		/* Vertical collision detection */
		eyeheight = ducking ? DuckHeight : EyeHeight;
		ground = !falling;
		if (falling)
			player_falling(&falling, &moving, &ground, &eyeheight, e);

		/* Horizontal collision detection */
		if (moving)
			player_moving(&moving, &falling, eyeheight, 1, e);

		SDL_Event ev;
		while(SDL_PollEvent(&ev))
			switch(ev.type)
			{
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					switch(ev.key.keysym.sym)
					{
						case 'w': wsad[0] = ev.type==SDL_KEYDOWN; break;
						case 's': wsad[1] = ev.type==SDL_KEYDOWN; break;
						case 'a': wsad[2] = ev.type==SDL_KEYDOWN; break;
						case 'd': wsad[3] = ev.type==SDL_KEYDOWN; break;
						case 'q': return (0);
						case ' ': /* jump */
							if (ground) { e->player.velocity.z += 0.5; falling = 1; }
							break;
						case SDLK_LCTRL: /* duck */
						case SDLK_RCTRL: ducking = ev.type==SDL_KEYDOWN; falling=1; break;
						default: break;
					}
					break;
				case SDL_QUIT:
					return (0); 
					break;
			}

		/* mouse aiming */
		int x,y;
		SDL_GetRelativeMouseState(&x,&y);
		e->player.angle += x * 0.03f;
		yaw          = clamp(yaw + y * 0.05f, -5, 5);
		e->player.yaw   = yaw - e->player.velocity.z * 0.5f;
		player_moving(&moving, &falling, eyeheight, 0, e);

		float move_vec[2] = {0.f, 0.f};
		if(wsad[0]) { move_vec[0] += e->player.anglecos*0.2f; move_vec[1] += e->player.anglesin*0.2f; }
		if(wsad[1]) { move_vec[0] -= e->player.anglecos*0.2f; move_vec[1] -= e->player.anglesin*0.2f; }
		if(wsad[2]) { move_vec[0] += e->player.anglesin*0.2f; move_vec[1] -= e->player.anglecos*0.2f; }
		if(wsad[3]) { move_vec[0] -= e->player.anglesin*0.2f; move_vec[1] += e->player.anglecos*0.2f; }
		int pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
		float acceleration = pushing ? 0.4 : 0.2;

		e->player.velocity.x = e->player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
		e->player.velocity.y = e->player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

		if(pushing) moving = 1;

		SDL_Delay(10);
	}
	return (0);
}