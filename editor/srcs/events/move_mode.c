/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:14:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 12:34:35 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			move_mode(t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;

	if (ui_mouseenter(m.x, m.y, rect))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN && env->editor.grid_drag == 0)
		{
			env->editor.grid_init_pos = m;
			env->editor.grid_drag = 1;
			return (1);
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{

			//if (vtx_transform((t_pos){-125, -125}, env).x < rect.x)
				env->editor.grid_translate.x += env->editor.grid_mouse_var.x;

			//if (vtx_transform((t_pos){-125, -125}, env).y < rect.y)
				env->editor.grid_translate.y += env->editor.grid_mouse_var.y;

			ft_bzero(&env->editor.grid_init_pos, sizeof(t_pos));
			ft_bzero(&env->editor.grid_mouse_var, sizeof(t_pos));
			env->editor.grid_drag = 0;
			return (1);
		}
		if (env->editor.grid_drag == 1)
		{
			env->editor.grid_mouse_var.x =
				(m.x - env->editor.grid_init_pos.x) / env->editor.grid_scale;
				
			env->editor.grid_mouse_var.y =
				(m.y - env->editor.grid_init_pos.y) / env->editor.grid_scale;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		ft_bzero(&env->editor.grid_init_pos, sizeof(t_pos));
		ft_bzero(&env->editor.grid_mouse_var, sizeof(t_pos));
		env->editor.grid_drag = 0;
		return (1);
	}
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}
