/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:41:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/22 17:42:18 by sgalasso         ###   ########.fr       */
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
	while (env->menu.status.on)
	{
		if (env->sdl.keycodes[SDL_SCANCODE_Q] || env->menu.status.quit)
			doom_exit();
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;

			SDL_PollEvent(&env->sdl.event);
			
			sdl_mainmenu_render(env);
			sdl_key_menu(env, env->sdl.event, env->sdl.keycodes);
		}
	}
}
