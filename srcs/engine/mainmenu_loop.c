/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:41:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 18:32:02 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	mainmenu_loop(t_env *env)
{
	env->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	(env->menu.status.gameover) ? env->menu.status.on = 1 : 0;
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
			draw_menu(env);
			update_render(env);
			sdl_keyhook_menu(env, env->sdl.event, env->sdl.keycodes);
		}
	}
}
