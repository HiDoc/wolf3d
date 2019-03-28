/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:10:00 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/28 14:38:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	sdl_render_game(t_env *env)
{
	dfs(env);
	handle_weapon(env, &env->time.frame);
	ui_put_fps(env, env->time.fps);
	// ui_minimap(env);
	print_hud(env);
	ui_draw_msg(env, &env->hud.is_txt, &env->time.tframe);
}

void	sdl_render_inventory(t_env *env)
{
	print_inventory(env);
	action_inventory(env, 0, 0);
	// (void)env;
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

int YourEventFilter(void *userdata, SDL_Event *event)
{
	t_env *env;

	env = (t_env *)userdata;
	if (event->type == SDL_MOUSEBUTTONDOWN && !env->player.actions.mouse_state)
		mouse_shoot(env);
	return (1);
}

int sdl_loop(t_env *env)
{
	const Uint8	*keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	t_vision *v;
	t_engine *e;

	ft_bzero(&env->time, sizeof(t_time));

	e = &env->engine;
	v = &e->player.vision;
	v->falling = 1;
	SDL_SetEventFilter(&YourEventFilter, (void *)env);
	while (1)
	{
		if (keycodes[SDL_SCANCODE_Q])
			return (0);
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;

			SDL_PollEvent(&env->sdl.event);
			if (!env->hud.inventory.is_active)
			{
				sdl_render(env, &sdl_render_game);
				// wpn_mouse_wheel(env, env->sdl.event);
				sdl_keyhook_game(env, env->sdl.event, keycodes);
				player_move(e, v, keycodes);

			}
			else
			{
				sdl_render(env, &sdl_render_inventory);
				sdl_keyhook_inventory(env, env->sdl.event, keycodes);
			}
		}
		ft_bzero(&env->sdl.event, sizeof(SDL_Event));
	}
	return (0);
}
