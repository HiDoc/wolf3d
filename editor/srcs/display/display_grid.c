/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:06:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 18:08:17 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static t_vec	calc_grid_hvec(int i, t_pos tr, t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	t_pos			origin;
	t_vec			vec;

	origin.x = rect.x + 425;
	vec.a.x = origin.x + (i + tr.x - (500 / 2)) * env->editor.grid_scale;
	vec.a.y = rect.y;
	vec.b.x = origin.x + (i + tr.x - (500 / 2)) * env->editor.grid_scale;
	vec.b.y = rect.y + rect.h;
	return (vec);
}

static t_vec	calc_grid_vvec(int i, t_pos tr, t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	t_pos			origin;
	t_vec			vec;

	origin.y = rect.y + 340;
	vec.a.x = rect.x;
	vec.a.y = origin.y + (i + tr.y - (500 / 2)) * env->editor.grid_scale;
	vec.b.x = rect.x + rect.w;
	vec.b.y = origin.y + (i + tr.y - (500 / 2)) * env->editor.grid_scale;
	return (vec);
}

void			display_grid(t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	t_vec			vec;
	Uint32			color;
	t_pos			tr;
	int				i;

	tr.x = env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	tr.y = env->editor.grid_translate.y + env->editor.grid_mouse_var.y;
	i = 0;
	while (i < 500)
	{
		if (i % 2 == 0)
		{
			color = (i % 10 == 0) ? 0X50FFFFFF : 0X20FFFFFF;
			vec = calc_grid_hvec(i, tr, env);
			if (point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect))
				ui_make_line(env->data->surface, vec, color);
			vec = calc_grid_vvec(i, tr, env);
			if (point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect))
				ui_make_line(env->data->surface, vec, color);
		}
		i++;
	}
	ui_make_rect(env->data->surface, get_element(E_R_RECT, env)->rect, C_WHITE);
}
