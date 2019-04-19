/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 20:13:49 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_grid(t_env *env)
{
	SDL_Rect	rect;
	t_vec		vec;
	Uint32		color;
	int			nb;
	int			i;

	// display interface area + grid
	nb = 0;
	i = 20 + env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	while (i < 870 && nb < 220)
	{
		color = (nb % 5 == 0) ? 0X50FFFFFF: 0X20FFFFFF;
		if (i > 20)
		{
			vec = (t_vec){(t_pos){i, 100}, (t_pos){i, 780}};
			ui_make_line(env->data->surface, vec, color);
		}
		i += 4 * env->pixel_value;
		nb++;
	}
	nb = 0;
	i = 100 + env->editor.grid_translate.y + env->editor.grid_mouse_var.y;
	while (i < 780 && nb < 180)
	{
		color = (nb % 5 == 0) ? 0X50FFFFFF: 0X20FFFFFF;
		if (i > 100)
		{
			vec = (t_vec){(t_pos){20, i}, (t_pos){870, i}};
			ui_make_line(env->data->surface, vec, color);
		}
		i += 4 * env->pixel_value;
		nb++;
	}
	rect = (SDL_Rect){20, 100, 850, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);
}

static void		display_infos(t_env *env)
{
	SDL_Rect	rect;
	t_vec		vec;

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
	if (env->sct_current)
	{
		rect = (SDL_Rect){190, 750, 0, 20};
		ui_make_string(rect, "size : ", env->data);
		rect = (SDL_Rect){240, 750, 0, 20};
		ui_make_nbrstring(rect, env->editor.vtx_size, env->data);
	}

	// display scale
	rect = (SDL_Rect){830, 750, 0, 20};
	ui_make_string(rect, "20", env->data);
	vec = (t_vec){(t_pos){820 - (20 * env->pixel_value), 765}, (t_pos){820, 765}};
	ui_make_line(env->data->surface, vec, C_WHITE);
	vec = (t_vec){(t_pos){820, 765}, (t_pos){820, 755}};
	ui_make_line(env->data->surface, vec, C_WHITE);
	vec = (t_vec){(t_pos){820 - (20 * env->pixel_value), 765},
	(t_pos){820 - (20 * env->pixel_value), 755}};
	ui_make_line(env->data->surface, vec, C_WHITE);
}

static int		is_vec_in_map(t_vec vec)
{
	return (vec.a.x > 0 && vec.a.y > 0 && vec.b.x > 0 && vec.b.y > 0
	&& vec.a.x < WIN_W && vec.a.y < WIN_H && vec.b.x < WIN_W && vec.b.y < WIN_H);
}

static t_vec	grid_transform(t_pos p1, t_pos p2, t_env *env)
{
	t_vec	vec;

	p1 = (t_pos){
	20 + (p1.x * env->pixel_value)
		+ env->editor.grid_translate.x + env->editor.grid_mouse_var.x,
	100 + (p1.y * env->pixel_value)
		+ env->editor.grid_translate.y + env->editor.grid_mouse_var.y};

	p2 = (t_pos){
	20 + (p2.x * env->pixel_value)
		+ env->editor.grid_translate.x + env->editor.grid_mouse_var.x,
	100 + (p2.y * env->pixel_value)
		+ env->editor.grid_translate.y + env->editor.grid_mouse_var.y};

	vec = (t_vec){p1, p2};
	return (vec);
}

void			display_sector(t_sct *sct, t_env *env)
{
	SDL_Rect	rect;
	t_w_vtx		*w_vtx;
	Uint32		color;
	t_vec		vec;


	if (env->editor.sct_hover == sct)
	{
		color = (env->editor.mouse_mode == 1) ? C_RED : C_GREEN;
	}
	else
	{
		color = (sct == sct_lst_end(env->sct_start)
		&& !sct->close) ? C_CYAN : C_WHITE;
	}
	w_vtx = sct->w_vtx_start;
	while (w_vtx && w_vtx->next)
	{
		vec = grid_transform(w_vtx->vtx->pos, w_vtx->next->vtx->pos, env);
		if (is_vec_in_map(vec))
		{
			if (w_vtx == env->editor.edg_hover)
				ui_make_line(env->data->surface, vec, C_BLUE);
			else
				ui_make_line(env->data->surface, vec, color);
			rect = (SDL_Rect){vec.a.x - 4, vec.a.y - 4, 8, 8};
			ui_make_full_rect(env->data->surface, rect, C_CYAN);
		}
		w_vtx = w_vtx->next;
	}
	if (sct->close)
	{
		vec = grid_transform(sct->w_vtx_start->vtx->pos,
		w_vtx_lst_end(sct->w_vtx_start)->vtx->pos, env);
		if (is_vec_in_map(vec))
		{
			if (w_vtx == env->editor.edg_hover)
				ui_make_line(env->data->surface, vec, C_BLUE);
			else
				ui_make_line(env->data->surface, vec, color);
			rect = (SDL_Rect){vec.b.x - 4, vec.b.y - 4, 8, 8};
			ui_make_full_rect(env->data->surface, rect, C_CYAN);
		}
	}
}

void			display_interface(t_env *env)
{
	Uint32		color;
	SDL_Rect	rect;
	t_vec		vec;

	display_grid(env);
	display_infos(env);

	// display all edges
	t_pos	p1;
	t_pos	p2;
	t_sct	*sct;
	sct = env->sct_start;
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
	if (env->sct_current)
	{
		p1 = (t_pos){
		20 + env->sct_current->w_vtx_current->vtx->pos.x
		* env->pixel_value + env->editor.grid_translate.x
		+ env->editor.grid_mouse_var.x,
		100 + env->sct_current->w_vtx_current->vtx->pos.y
		* env->pixel_value + env->editor.grid_translate.y
		+ env->editor.grid_mouse_var.y};

		p2 = (t_pos){env->data->mouse.x,env->data->mouse.y};

		vec = (t_vec){p1, p2};
		ui_make_line(env->data->surface, vec, C_CYAN);
		rect = (SDL_Rect){vec.a.x - 4, vec.a.y - 4, 8, 8};
		ui_make_full_rect(env->data->surface, rect, C_CYAN);
	}

	// display vtx hovering
	t_circ	circ;
	if (env->editor.vtx_hover)
	{
		circ = (t_circ){
		20 + env->editor.vtx_hover->pos.x * env->pixel_value
		+ env->editor.grid_translate.x + env->editor.grid_mouse_var.x,
		100 + env->editor.vtx_hover->pos.y * env->pixel_value
		+ env->editor.grid_translate.y + env->editor.grid_mouse_var.y,
		10, 0xFFFFFFFF};
		ui_make_circle(circ, env->data);
	}

	// display objects
	t_object	*obj = env->objects;
	while (obj)
	{
		if (obj->category == CONSUMABLE)
			color = C_GREEN;
		else if (obj->category == ENTITY)
			color = C_RED;
		else
			color = C_WHITE;

		p1 = (t_pos){
		20 + obj->pos.x * env->pixel_value + env->editor.grid_translate.x
		+ env->editor.grid_mouse_var.x,
		100 + obj->pos.y * env->pixel_value + env->editor.grid_translate.y
		+ env->editor.grid_mouse_var.y};

		rect = (SDL_Rect){p1.x - 5, p1.y - 5, 10, 10};
		ui_make_rect(env->data->surface, rect, color);
		obj = obj->next;
	}
}
