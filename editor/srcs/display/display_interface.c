/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/01 13:50:44 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int				point_in_rect(t_pos pos, SDL_Rect rect) // set in utils
{
	return (pos.x >= rect.x && pos.x <= rect.x + rect.w
	&& pos.y >= rect.y && pos.y <= rect.y + rect.h);
}

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
	while (i < 250)
	{
		color = (i % 5 == 0) ? 0X50FFFFFF: 0X20FFFFFF;

		vec.a = (t_pos){
			origin.x + (i + translate.x - (250 / 2)) * env->grid_scale,
			rect.y};
		vec.b = (t_pos){
			origin.x + (i + translate.x - (250 / 2)) * env->grid_scale,
			rect.y + rect.h};

		if (point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect))
			ui_make_line(env->data->surface, vec, color);
		i++;
	}
	i = 0;
	while (i < 250)
	{
		color = (i % 5 == 0) ? 0X50FFFFFF: 0X20FFFFFF;

		vec.a = (t_pos){
			rect.x,
			origin.y + (i + translate.y - (250 / 2)) * env->grid_scale};
		vec.b = (t_pos){
			rect.x + rect.w,
			origin.y + (i + translate.y - (250 / 2)) * env->grid_scale};

		if (point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect))
			ui_make_line(env->data->surface, vec, color);
		i++;
	}
	ui_make_rect(env->data->surface, get_element(E_R_RECT, env)->rect, C_WHITE);

}

static void		display_infos(t_env *env)
{
	SDL_Rect	rect;
	//t_vec		vec;

	// display position
	rect = (SDL_Rect){30, 750, 0, 20};
	ui_make_string(rect, "x : ", env->data);
	rect = (SDL_Rect){60, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.x, env->data);
	rect = (SDL_Rect){110, 750, 0, 20};
	ui_make_string(rect, "y : ", env->data);
	rect = (SDL_Rect){140, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.y, env->data);

	// display_size
	if (env->editor.sct_current)
	{
		rect = (SDL_Rect){190, 750, 0, 20};
		ui_make_string(rect, "size : ", env->data);
		rect = (SDL_Rect){240, 750, 0, 20};
		ui_make_nbrstring(rect,
			env->editor.sct_current->w_vtx_current->size, env->data);
	}

	// display scale
	/*rect = (SDL_Rect){830, 750, 0, 20};
	ui_make_string(rect, "20", env->data);
	vec = (t_vec){(t_pos){820 - (20 * env->pixel_value), 765}, (t_pos){820, 765}};
	ui_make_line(env->data->surface, vec, C_WHITE);
	vec = (t_vec){(t_pos){820, 765}, (t_pos){820, 755}};
	ui_make_line(env->data->surface, vec, C_WHITE);
	vec = (t_vec){(t_pos){820 - (20 * env->pixel_value), 765},
	(t_pos){820 - (20 * env->pixel_value), 755}};
	ui_make_line(env->data->surface, vec, C_WHITE);*/
}

void			display_sector(t_sct *sct, t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	SDL_Rect		vtxrect;
	t_w_vtx			*w_vtx;
	Uint32			color;
	t_vec			vec;


	if (env->editor.sct_hover == sct)
	{
		color = (env->editor.mouse_mode == 1) ? C_RED : C_GREEN;
	}
	else
	{
		color = (sct == env->editor.sct_start && !sct->close) ? C_GREEN : C_WHITE;
	}
	w_vtx = sct->w_vtx_start;
	while (w_vtx && w_vtx->next)
	{
		vec.a = vtx_transform(w_vtx->vtx->pos, env);
		vec.b = vtx_transform(w_vtx->next->vtx->pos, env);
		if ((point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect)))
		{
			if (w_vtx == env->editor.edg_hover)
				ui_make_line(env->data->surface, vec, C_BLUE);
			else
				ui_make_line(env->data->surface, vec, color);
			if (point_in_rect(vec.a, rect))
			{
				vtxrect = (SDL_Rect){vec.a.x - 4, vec.a.y - 4, 8, 8};
				ui_make_full_rect(env->data->surface, vtxrect, C_CYAN);
			}
		}
		w_vtx = w_vtx->next;
	}
	if (sct->close)
	{
		vec.a = vtx_transform(sct->w_vtx_start->vtx->pos, env);
		vec.b = vtx_transform(w_vtx_lst_end(sct->w_vtx_start)->vtx->pos, env);
		if ((point_in_rect(vec.a, rect) && point_in_rect(vec.b, rect)))
		{
			if (w_vtx == env->editor.edg_hover)
				ui_make_line(env->data->surface, vec, C_BLUE);
			else
				ui_make_line(env->data->surface, vec, color);
			if (point_in_rect(vec.b, rect))
			{
				vtxrect = (SDL_Rect){vec.b.x - 4, vec.b.y - 4, 8, 8};
				ui_make_full_rect(env->data->surface, vtxrect, C_CYAN);
			}
		}
	}
}

void			display_interface(t_env *env)
{
	Uint32			color;
	SDL_Rect		rect;
	t_pos			pos;
	t_vec			vec;

	display_grid(env);
	display_infos(env);

	// display all edges
	t_sct	*sct;
	sct = env->editor.sct_start;
	while (sct)
	{
		if (sct != env->editor.sct_hover)
			display_sector(sct, env);
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

	// display objects
	t_object	*obj = env->editor.objects;
	while (obj)
	{
		if (obj->category == CONSUMABLE)
			color = C_GREEN;
		else if (obj->category == ENTITY)
			color = C_RED;
		else
			color = C_WHITE;

		pos = vtx_transform(obj->pos, env);
		if (point_in_rect(pos, get_element(E_R_RECT, env)->rect))
		{
			rect = (SDL_Rect){pos.x - 5, pos.y - 5, 10, 10};
			ui_make_rect(env->data->surface, rect, color);
			if (obj->category == SPECIAL
				&& env->editor.obj_elem->id == 0 && env->editor.spawn_set == 0)
			{
				// spawn dir
				ui_draw_vector(env->data->surface, pos,
				env->editor.spawn_dir, 0, 10, C_WHITE);
			}
		}
		obj = obj->next;
	}
}
