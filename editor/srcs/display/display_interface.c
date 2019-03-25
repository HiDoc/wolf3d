/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 16:04:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_infos(t_env *env)
{
	t_rect		rect;

	// display position
	rect = (t_rect){30, 750, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "x : ", env->data);
	rect = (t_rect){60, 750, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->data->mouse_x, env->data);
	rect = (t_rect){110, 750, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "y : ", env->data);
	rect = (t_rect){140, 750, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->data->mouse_y, env->data);

	// display_size
	rect = (t_rect){190, 750, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "size : ", env->data);
	rect = (t_rect){240, 750, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->vtx_size, env->data);
}

void			display_interface(t_env *env)
{
	t_rect		rect;

	// display interface area
	rect = (t_rect){20, 100, 850, 680, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);

	display_infos(env);

	// display all edges
	t_vec	vec;
	t_sct	*sct;
	t_vtx	*vtx;
	Uint32	color;
	sct = env->sct_start;
	while (sct)
	{
		if (sct != env->sct_hover)
		{
			vtx = sct->vtx_start;
			color = (sct == env->sct_end && !sct->close) ? C_CYAN : C_WHITE;
			while (vtx->next)
			{
				vec = (t_vec){vtx->pos, vtx->next->pos};
				ui_make_dotted_line(env->data->surface, vec, color);
				vtx = vtx->next;
			}
			if (sct->close)
			{
				vec = (t_vec){sct->vtx_start->pos, sct->vtx_end->pos};
				ui_make_line(env->data->surface, vec, color);
			}
		}
		sct = sct->next;
	}
	// display hovered one overflowing the others
	if (env->sct_hover)
	{
		color = (env->mouse_mode == 1) ? C_RED : C_GREEN;
		vtx = env->sct_hover->vtx_start;
		while (vtx->next)
		{
			vec = (t_vec){vtx->pos, vtx->next->pos};
			ui_make_line(env->data->surface, vec, color);
			vtx = vtx->next;
		}
		if (env->sct_hover->close)
		{
			vec = (t_vec){env->sct_hover->vtx_start->pos,
			env->sct_hover->vtx_end->pos};
			ui_make_line(env->data->surface, vec, color);
		}
	}
		
	// display vtx hovering
	t_circ	circ;
	if (env->vtx_hover)
	{
		circ = (t_circ){env->vtx_hover->pos.x,
		env->vtx_hover->pos.y, 10, 0xFFFFFFFF};
		ui_make_circle(circ, env->data);
	}

	// display current edge
	if (env->sct_current)
	{
		vec = (t_vec){env->sct_current->vtx_current->pos, env->data->mouse};
		ui_make_line(env->data->surface, vec, C_CYAN);
	}
}
