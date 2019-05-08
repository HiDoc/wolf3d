/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:01:18 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 20:41:40 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	action_endlevel(t_env *e, int level)
{
	Uint32	*t;

	if (e->finish)
	{
		e->menu.status.inter = 0;
		e->finish = 0;
		t = &e->levels[e->curr_lvl]->tplay;
		*t = SDL_GetTicks() - *t;
		if (e->curr_lvl < e->nb_levels - 1)
			e->levels[e->curr_lvl + 1]->tplay = SDL_GetTicks();
	}
	if (level == e->nb_levels - 1)
		display_credits(e);
}

void	loop_intro(t_env *env, int level)
{
	env->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	while (env->menu.status.inter)
	{
		if (env->sdl.keycodes[SDL_SCANCODE_Q] || env->menu.status.quit
				|| env->sdl.event.type == SDL_QUIT)
			doom_exit();
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;
			draw_inter(env, level);
			update_render(env);
			SDL_WaitEvent(&env->sdl.event);
			if (env->sdl.keycodes[SDL_SCANCODE_RETURN])
				env->menu.status.inter = 0;
		}
	}
}
