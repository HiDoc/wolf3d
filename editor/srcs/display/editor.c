/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/14 15:43:16 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	display_interface(t_env *env)
{
	t_rect		rect;

	// display interface area
	rect = (t_rect){20, 100, 850, 680, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);

	// display position
	rect = (t_rect){30, 750, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "x : ", env->data);
	rect = (t_rect){60, 750, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->data->mouse_x, env->data);
	rect = (t_rect){110, 750, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "y : ", env->data);
	rect = (t_rect){140, 750, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->data->mouse_y, env->data);
	/*rect = (t_rect){190, 750, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "size : ", env->data);
	rect = (t_rect){240, 750, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->sector[env->sct_index].cur_vrx_size, env->data);*/
	
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
				ui_make_line(env->data->surface, vec, color);
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
		ui_make_circle(circ, 0, 0, env->data);
	}

	// display current edge
	if (env->sct_current)
	{
		vec = (t_vec){env->sct_current->vtx_current->pos, env->data->mouse};
		ui_make_line(env->data->surface, vec, C_CYAN);
	}
}

static void	display_selection(t_env *env)
{
	t_rect		rect;

	// display selection area
	rect = (t_rect){890, 100, 290, 250, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);

	// display selected
	/*rect = (t_rect){30, 110, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "S ", env->data);
	rect = (t_rect){60, 110, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->cur_sct, env->data);*/
	/*rect = (t_rect){30, 130, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "E ", env->data);
	rect = (t_rect){60, 130, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->cur_edg, env->data);
	rect = (t_rect){30, 150, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "V ", env->data);
	rect = (t_rect){60, 150, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->cur_vrx, env->data);*/

	// display inputs
	rect = (t_rect){900, 110, 0, 20, 0xffffffff};
	ui_make_string(rect, "Selected vertex [S3] [V2]", env->data);
	rect = (t_rect){900, 150, 0, 20, 0xffffffff};
	ui_make_string(rect, "Height", env->data);
	rect = (t_rect){900, 180, 140, 20, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){900, 210, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Texture", env->data);
	rect = (t_rect){900, 240, 140, 20, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
}

void		editor(t_env *env)
{
	t_rect		rect;

	display_interface(env);
	display_selection(env);

	// display buttons
	rect = (t_rect){20, 20, 100, 40, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){45, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "New", env->data);
	rect = (t_rect){130, 20, 125, 40, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){155, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "Upload", env->data);
	rect = (t_rect){300, 20, 100, 40, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){324, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "Save", env->data);

	// display nb frames
	rect = (t_rect){1100, 20, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->data->nb_frames, env->data);

	// display nb element
	rect = (t_rect){900, 600, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb sectors : ", env->data);
	rect = (t_rect){1040, 600, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->nb_sct, env->data);
	/*rect = (t_rect){900, 630, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb edges : ", env->data);
	rect = (t_rect){1040, 630, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->edg_index + 1, env->data);*/
	rect = (t_rect){900, 660, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb vertex : ", env->data);
	rect = (t_rect){1040, 660, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->nb_vtx, env->data);

	// display mouse mode
	rect = (t_rect){720, 20, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Mouse mode : ", env->data);
	rect = (t_rect){850, 20, 0, 20, 0xFFFFFFFF};
	if (env->mouse_mode == 0)
		ui_make_string(rect, "select", env->data);
	else
		ui_make_string(rect, "draw", env->data);
}
