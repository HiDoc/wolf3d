/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:17:00 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/26 17:01:00 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	mouse_shoot(t_env *env)
{
	//t_line	line;

	//line_init(env, &line, env->w_map, 400);
	env->player.actions.is_shooting = 1;
	Mix_PlayChannel(-1, env->sounds.shot, 0);
	SDL_FlushEvent(SDL_MOUSEBUTTONUP);
	return (0);
}

int	sdl_mouse_click(t_env *env, int x, int y)
{
	(void)x;
	(void)y;
	mouse_shoot(env);
	return (0);
}
