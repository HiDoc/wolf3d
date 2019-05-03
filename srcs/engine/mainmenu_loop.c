/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:41:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/02 14:20:14 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int				sdl_mainmenu_render(t_env *env)
{
	draw_menu(env);
	SDL_UpdateTexture(env->sdl.texture, NULL,
		env->sdl.surface->pixels, env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
	return (1);
}

void					mainmenu_loop(t_env *env)
{
	env->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	(env->menu.status.gameover) ? env->menu.status.on = 1 : 0;
	set_msc_menu(env, &env->menu.status);
	while (env->menu.status.on)
	{
		if (env->sdl.keycodes[SDL_SCANCODE_Q] || env->menu.status.quit)
			doom_exit();
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;

			SDL_PollEvent(&env->sdl.event);
			if (env->menu.status.gameover
				&& env->sdl.keycodes[SDL_SCANCODE_RETURN])
			{
				env->menu.status.gameover = 0;
				env->menu.status.main_menu = 1;
			}
			sdl_mainmenu_render(env);
			sdl_key_menu(env, env->sdl.event, env->sdl.keycodes);
		}
	}
}
