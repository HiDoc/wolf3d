/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:14:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/05 19:56:41 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			move_mode(t_env *env)
{
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect  rect = (SDL_Rect){20, 100, 850, 680};

	if (event.type == SDL_MOUSEBUTTONDOWN && env->grid_drag == 0
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
	{
		env->grid_init_pos = env->data->mouse;
		env->grid_drag = 1;
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		ft_bzero(&env->grid_init_pos, sizeof(t_pos));
		env->grid_drag = 0;
	}

	if (env->grid_drag == 1)
	{
		env->grid_translate.x = (env->data->mouse.x - env->grid_init_pos.x);
		env->grid_translate.y = (env->data->mouse.y - env->grid_init_pos.y);
		return (1);
	}

	return (0);
}
