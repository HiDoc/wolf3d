/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 13:51:51 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_grid(t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	t_pos			translate;
	t_pos			origin;;
	t_vec			vec;
	Uint32			color;
	int				i;

	origin.x = rect.x + 425;
	origin.y = rect.y + 340;

	translate.x = env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	translate.y = env->editor.grid_translate.y + env->editor.grid_mouse_var.y;

	i = 0;
	while (i < 500)
	{
		if (i % 2 == 0)
		{
			color = (i % 10 == 0) ? 0X50FFFFFF: 0X20FFFFFF;
	
			vec.a = (t_pos){
				origin.x + (i + translate.x - (500 / 2)) * env->editor.grid_scale,
				rect.y};
			vec.b = (t_pos){
				origin.x + (i + translate.x - (500 / 2)) * env->editor.grid_scale,
				rect.y + rect.h};
	
			if (point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect))
				ui_make_line(env->data->surface, vec, color);
		}
		i++;
	}
	i = 0;
	while (i < 500)
	{
		if (i % 2 == 0)
		{
			color = (i % 10 == 0) ? 0X50FFFFFF: 0X20FFFFFF;
	
			vec.a = (t_pos){
				rect.x,
				origin.y + (i + translate.y - (500 / 2)) * env->editor.grid_scale};
			vec.b = (t_pos){
				rect.x + rect.w,
				origin.y + (i + translate.y - (500 / 2)) * env->editor.grid_scale};
	
			if (point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect))
				ui_make_line(env->data->surface, vec, color);
		}
		i++;
	}
	ui_make_rect(env->data->surface, get_element(E_R_RECT, env)->rect, C_WHITE);

}

static void		display_infos(t_env *env)
{
	SDL_Rect	rect;

	// display position
	rect = (SDL_Rect){30, 750, 0, 20};
	ui_make_string(rect, "x : ", C_WHITE, env->data);
	rect = (SDL_Rect){60, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.x, C_WHITE, env->data);
	rect = (SDL_Rect){110, 750, 0, 20};
	ui_make_string(rect, "y : ", C_WHITE, env->data);
	rect = (SDL_Rect){140, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.y, C_WHITE, env->data);

	// display_size
	if (env->editor.sct_current)
	{
		rect = (SDL_Rect){190, 750, 0, 20};
		ui_make_string(rect, "size : ", C_WHITE, env->data);
		rect = (SDL_Rect){240, 750, 0, 20};
		ui_make_nbrstring(rect,
			env->editor.sct_current->w_vtx_current->size, C_WHITE, env->data);
	}
}

void			display_sector(t_sct *sct, t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	SDL_Rect		vtxrect;
	t_w_vtx			*w_vtx;
	Uint32			color;
	t_vec			vec;

	if (env->editor.sct_hover == sct)
		color = C_GREEN;
	else
		color = (sct == env->editor.sct_start && !sct->close) ? C_GREEN : C_WHITE;

	w_vtx = sct->w_vtx_start;
	while (w_vtx && w_vtx->next)
	{
		vec.a = vtx_transform(w_vtx->vtx->pos, env);
		vec.b = vtx_transform(w_vtx->next->vtx->pos, env);
		if (w_vtx == env->editor.edg_hover)
			ui_make_clipped_line(env->data->surface, vec, rect, C_BLUE);
		else
			ui_make_clipped_line(env->data->surface, vec, rect, color);
		if (point_in_rect(vec.a, rect))
		{
			vtxrect = (SDL_Rect){vec.a.x - 4, vec.a.y - 4, 8, 8};
			ui_make_full_rect(env->data->surface, vtxrect, C_CYAN);
		}
		w_vtx = w_vtx->next;
	}
	if (sct->close)
	{
		vec.a = vtx_transform(sct->w_vtx_start->vtx->pos, env);
		vec.b = vtx_transform(w_vtx_lst_end(sct->w_vtx_start)->vtx->pos, env);
		if (w_vtx == env->editor.edg_hover)
			ui_make_clipped_line(env->data->surface, vec, rect, C_BLUE);
		else
			ui_make_clipped_line(env->data->surface, vec, rect, color);
		if (point_in_rect(vec.b, rect))
		{
			vtxrect = (SDL_Rect){vec.b.x - 4, vec.b.y - 4, 8, 8};
			ui_make_full_rect(env->data->surface, vtxrect, C_CYAN);
		}
	}
}

static void		display_spaces(t_env *env)
{
	SDL_Rect		rect;
	t_pos			pos;
	t_vec			vec;

	t_sct	*sct;
	sct = env->editor.sct_start;
	while (sct)
	{
		if (sector_in_rect(sct, get_element(E_R_RECT, env)->rect, env))
		{
			if (sct != env->editor.sct_hover)
				display_sector(sct, env);
		}
		sct = sct->next;
	}
	// display hovered one overflowing the others
	if (env->editor.sct_hover)
		display_sector(env->editor.sct_hover, env);

	// display current edge
	if (env->editor.sct_current)
	{
		vec.a = vtx_transform(env->editor.sct_current->w_vtx_current->vtx->pos, env);
		vec.b = (t_pos){env->data->mouse.x,env->data->mouse.y};

		ui_make_line(env->data->surface, vec, C_CYAN);
		rect = (SDL_Rect){vec.a.x - 4, vec.a.y - 4, 8, 8};
		ui_make_full_rect(env->data->surface, rect, C_CYAN);
	}

	// display vtx hovering
	t_circ	circ;
	if (env->editor.vtx_hover)
	{
		pos = vtx_transform(env->editor.vtx_hover->pos, env);
		circ = (t_circ){pos, 10, 0xFFFFFFFF};
		ui_make_circle(circ, env->data);
	}
}

static void		display_objects(t_env *env)
{
	Uint32		color;
	t_pos		pos;
	SDL_Rect	rect;

	// display objects
	t_object	*obj = env->editor.objects;
	while (obj)
	{
		pos = vtx_transform(obj->pos, env);
		if (point_in_rect(pos, get_element(E_R_RECT, env)->rect))
		{
			if (obj->dd == DD_CONS)
				color = C_GREEN;
			else if (obj->dd == DD_NTTY)
				color = C_RED;
			else
				color = C_WHITE;
			rect = (SDL_Rect){pos.x - 5, pos.y - 5, 10, 10};
			ui_make_rect(env->data->surface, rect, color);
			if (obj->dd == DD_SPEC && env->editor.spawn_set == 2)
			{
				// spawn dir
				ui_draw_vector(env->data->surface, pos,
				env->editor.spawn_dir, 10, C_WHITE);
			}
		}
		obj = obj->next;
	}
}

void			display_interface(t_env *env)
{
	display_grid(env);
	display_infos(env);
	display_spaces(env);
	display_objects(env);
}
