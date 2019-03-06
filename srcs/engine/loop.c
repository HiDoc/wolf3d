#include "doom.h"

int		sdl_render(t_env *env, t_engine *e, void (*f)(t_env *env))
{
	SDL_LockSurface(e->surface);
	f(env);
	SDL_UnlockSurface(e->surface);
	if (env->sdl.texture == NULL)
		env->sdl.texture = SDL_CreateTextureFromSurface(env->sdl.renderer, e->surface);
	else
	{
		SDL_DestroyTexture(env->sdl.texture);
		env->sdl.texture = SDL_CreateTextureFromSurface(env->sdl.renderer, e->surface);
	}
	SDL_RenderClear(env->sdl.renderer);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
	return (1);
}

/*
** Mouse aiming !
*/
int		sdl_mouse(t_engine *e, t_vision *v)
{
	int				x;
	int				y;

	SDL_GetRelativeMouseState(&x,&y);
	e->player.angle += x * 0.03f;
	v->yaw = clamp(v->yaw + y * 0.05f, -5, 5);
	e->player.yaw = v->yaw - e->player.velocity.z * 0.5f;
	player_moving(v, 0, e);
	return (1);
}

int		sdl_loop(t_env *env)
{

	int				wsad[4] = {0,0,0,0};
	t_vision        v;
	t_engine		*e;

	e = &env->engine;
	v = (t_vision) {0, 1, 0, 0, 0, 0};
	while (1)
	{
		sdl_render(env, e, &draw_screen);
		player_collision(e, &v);
		SDL_Event ev;

		while (SDL_PollEvent(&ev))
		{
			// SDL_WaitEvent(&ev);
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
							// if (v.ground) {
								e->player.velocity.z += 0.5; v.falling = 1;
							// }
							break;
						case SDLK_LCTRL: /* duck */
						case SDLK_RCTRL: v.ducking = ev.type==SDL_KEYDOWN; v.falling=1; break;
						default: break;
					}
					break;
				case SDL_QUIT:
					return (0);
					break;
			}
		}

		sdl_mouse(e, &v);
		float move_vec[2] = {0.f, 0.f};
		if(wsad[0]) { move_vec[0] += e->player.anglecos * 0.2f; move_vec[1] += e->player.anglesin * 0.2f; }
		if(wsad[1]) { move_vec[0] -= e->player.anglecos * 0.2f; move_vec[1] -= e->player.anglesin * 0.2f; }
		if(wsad[2]) { move_vec[0] += e->player.anglesin * 0.2f; move_vec[1] -= e->player.anglecos * 0.2f; }
		if(wsad[3]) { move_vec[0] -= e->player.anglesin * 0.2f; move_vec[1] += e->player.anglecos * 0.2f; }
		int pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
		float acceleration = pushing ? 0.4 : 0.2;

		e->player.velocity.x = e->player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
		e->player.velocity.y = e->player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

		if (pushing)
			v.moving = 1;
		SDL_Delay(10);
	}
	return (0);
}