#include "doom.h"

void	sdl_render_game(t_env *env)
{
	dfs(env);
	//loop_frames(env, &env->time.frame);
	ui_put_fps(env, env->time.fps);
	//print_hud(env);
	ui_minimap(env);
	//ui_draw_msg(env, &env->player.hud.is_txt, &env->time.tframe);
}

void	sdl_render_inventory(t_env *env)
{
	print_inventory(env);
	action_inventory(env, 0, 0);
}

int sdl_render(t_env *env, void (*f)(t_env *env))
{
	(void)f;
	SDL_LockSurface(env->sdl.surface);
	f(env);
	SDL_UnlockSurface(env->sdl.surface);
	SDL_UpdateTexture(env->sdl.texture,
					NULL,
					env->sdl.surface->pixels,
					env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
	return (1);
}

int sdl_loop(t_env *env)
{
	t_vision *v;
	t_engine *e;
	const Uint8	*keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);

	ft_bzero(&env->time, sizeof(t_time));

	e = &env->engine;
	v = &e->player.vision;
	v->falling = 1;
	while (1)
	{
		SDL_Event ev;
		if (keycodes[SDL_SCANCODE_Q])
			return (0);
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;
			SDL_PollEvent(&ev);
			if (!env->player.inventory.ui.is_active)
			{
				sdl_render(env, &sdl_render_game);

				//wpn_mouse_wheel(env, ev);
				//mouse_shoot(env);

				sdl_mouse(e, v);
				//sdl_keyhook_game(env, ev, keycodes);
				player_collision(e, v, env->player.actions.is_flying);
				sdl_set_velocity(env, v, keycodes);
			}
			else
			{
				sdl_render(env, &sdl_render_inventory);
				sdl_keyhook_inventory(env, ev, keycodes);
			}
		}
	}
	return (0);
}
