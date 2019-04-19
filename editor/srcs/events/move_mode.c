/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:14:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/18 20:50:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			move_mode(t_env *env)
{
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect  rect = (SDL_Rect){20, 100, 850, 680};

	if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN && env->editor.grid_drag == 0)
		{
			env->editor.grid_init_pos = env->data->mouse;
			env->editor.grid_drag = 1;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			env->editor.grid_translate.x += env->editor.grid_mouse_var.x;
			env->editor.grid_translate.y += env->editor.grid_mouse_var.y;
			ft_bzero(&env->editor.grid_init_pos, sizeof(t_pos));
			ft_bzero(&env->editor.grid_mouse_var, sizeof(t_pos));
			env->editor.grid_drag = 0;
		}
		if (env->editor.grid_drag == 1)
		{
			env->editor.grid_mouse_var.x =
			(env->data->mouse.x - env->editor.grid_init_pos.x);
			if (env->editor.grid_translate.x + env->editor.grid_mouse_var.x > 0)
				env->editor.grid_mouse_var.x = -env->editor.grid_translate.x;
			env->editor.grid_mouse_var.y =
			(env->data->mouse.y - env->editor.grid_init_pos.y);
			if (env->editor.grid_translate.y + env->editor.grid_mouse_var.y > 0)
				env->editor.grid_mouse_var.y = -env->editor.grid_translate.y;
			return (1);
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		ft_bzero(&env->editor.grid_init_pos, sizeof(t_pos));
		ft_bzero(&env->editor.grid_mouse_var, sizeof(t_pos));
		env->editor.grid_drag = 0;
	}
	if (env->data->mouse.x || env->data->mouse.y)
		return (1);
	return (0);
}
