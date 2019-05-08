/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 16:36:47 by sgalasso         ###   ########.fr       */
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

static void		display_grid(t_env *env)
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

static void		display_infos(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){30, 750, 0, 20};
	ui_make_string(rect, "x : ", C_WHITE, env->data);
	rect = (SDL_Rect){60, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.x, C_WHITE, env->data);
	rect = (SDL_Rect){110, 750, 0, 20};
	ui_make_string(rect, "y : ", C_WHITE, env->data);
	rect = (SDL_Rect){140, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.y, C_WHITE, env->data);
	if (env->editor.sct_current)
	{
		rect = (SDL_Rect){190, 750, 0, 20};
		ui_make_string(rect, "size : ", C_WHITE, env->data);
		rect = (SDL_Rect){240, 750, 0, 20};
		ui_make_nbrstring(rect,
			env->editor.sct_current->w_vtx_current->size, C_WHITE, env->data);
	}
}

static void		display_edge(t_w_vtx *a, t_w_vtx *b, Uint32 color, t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	SDL_Rect		vtxrect;
	t_vec			vec;

	vec.a = vtx_transform(a->vtx->pos, env);
	vec.b = vtx_transform(b->vtx->pos, env);
	if (a == env->editor.edg_hover)
		ui_make_clipped_line(env->data->surface, vec, rect, C_BLUE);
	else
		ui_make_clipped_line(env->data->surface, vec, rect, color);
	if (point_in_rect(vec.a, rect))
	{
		vtxrect = (SDL_Rect){vec.a.x - 4, vec.a.y - 4, 8, 8};
		ui_make_full_rect(env->data->surface, vtxrect, C_CYAN);
	}
}

void			display_sector(t_sct *sct, t_env *env)
{
	t_w_vtx			*w_vtx;
	Uint32			color;

	color = C_WHITE;
	if (sct == env->editor.sct_hover
	|| (sct == env->editor.sct_start && !sct->close))
		color = C_GREEN;
	w_vtx = sct->w_vtx_start;
	while (w_vtx && w_vtx->next)
	{
		display_edge(w_vtx, w_vtx->next, color, env);
		w_vtx = w_vtx->next;
	}
	if (sct->close)
		display_edge(sct->w_vtx_start,
		w_vtx_lst_end(sct->w_vtx_start), color, env);
}

static void		display_spaces(t_env *env)
{
	SDL_Rect		rect;
	t_vec			vec;
	t_sct			*sct;

	sct = env->editor.sct_start;
	while (sct)
	{
		rect = get_element(E_R_RECT, env)->rect;
		if (sector_in_rect(sct, rect, env) && sct != env->editor.sct_hover)
			display_sector(sct, env);
		sct = sct->next;
	}
	if (env->editor.sct_hover)
		display_sector(env->editor.sct_hover, env);
	if (env->editor.sct_current)
	{
		vec.a = vtx_transform(
			env->editor.sct_current->w_vtx_current->vtx->pos, env);
		vec.b = (t_pos){
			env->data->mouse.x, env->data->mouse.y};
		ui_make_line(env->data->surface, vec, C_CYAN);
		rect = (SDL_Rect){vec.a.x - 4, vec.a.y - 4, 8, 8};
		ui_make_full_rect(env->data->surface, rect, C_CYAN);
	}
}

static void		display_objects(t_env *env)
{
	t_pos		pos;
	SDL_Rect	rect;
	t_object	*obj;

	obj = env->editor.objects;
	while (obj)
	{
		pos = vtx_transform(obj->pos, env);
		if (point_in_rect(pos, get_element(E_R_RECT, env)->rect))
		{
			rect = (SDL_Rect){pos.x - 5, pos.y - 5, 10, 10};
			ui_make_rect(env->data->surface, rect, obj->color);
			if (obj->dd == DD_SPEC && env->editor.spawn_set == 2)
			{
				ui_draw_vector(env->data->surface, pos,
				env->editor.spawn_dir, 10);
			}
		}
		obj = obj->next;
	}
}

void			display_interface(t_env *env)
{
	t_circ		circ;

	display_grid(env);
	display_infos(env);
	display_spaces(env);
	if (env->editor.vtx_hover)
	{
		circ = (t_circ){
			vtx_transform(env->editor.vtx_hover->pos, env), 10, C_WHITE};
		ui_make_circle(circ, env->data);
	}
	display_objects(env);
}
