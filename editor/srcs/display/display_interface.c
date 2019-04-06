/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/06 16:30:53 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
	rect = (SDL_Rect){190, 750, 0, 20};
	ui_make_string(rect, "size : ", env->data);
	rect = (SDL_Rect){240, 750, 0, 20};
	ui_make_nbrstring(rect, env->vtx_size, env->data);

	// display bloc_size
	rect = (SDL_Rect){840, 750, 0, 20};
	ui_make_nbrstring(rect, 20, env->data);
	vec = (t_vec){(t_pos){830 - (20 * env->pixel_value), 765}, (t_pos){830, 765}};
	ui_make_line(env->data->surface, vec, C_WHITE);
	vec = (t_vec){(t_pos){830, 765}, (t_pos){830, 755}};
	ui_make_line(env->data->surface, vec, C_WHITE);
	vec = (t_vec){(t_pos){830 - (20 * env->pixel_value), 765},
	(t_pos){830 - (20 * env->pixel_value), 755}};
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
		+ env->grid_translate.x + env->grid_mouse_var.x,
	100 + (p1.y * env->pixel_value)
		+ env->grid_translate.y + env->grid_mouse_var.y};

	p2 = (t_pos){
	20 + (p2.x * env->pixel_value)
		+ env->grid_translate.x + env->grid_mouse_var.x,
	100 + (p2.y * env->pixel_value)
		+ env->grid_translate.y + env->grid_mouse_var.y};

	vec = (t_vec){p1, p2};
	return (vec);
}

void			display_sector(t_sct *sct, t_env *env)
{
	Uint32		color;
	t_vec		vec;
	t_vtx		*vtx;


	if (env->sct_hover)
		color = (env->mouse_mode == 1) ? C_RED : C_GREEN;
	else
		color = (sct == env->sct_end && !sct->close) ? C_CYAN : C_WHITE;
	vtx = sct->vtx_start;
	while (vtx->next)
	{
		vec = grid_transform(vtx->pos, vtx->next->pos, env);
		if (is_vec_in_map(vec))
			ui_make_line(env->data->surface, vec, color);
		vtx = vtx->next;
	}
	if (sct->close)
	{
		vec = grid_transform(sct->vtx_start->pos, sct->vtx_end->pos, env);
		if (is_vec_in_map(vec))
			ui_make_line(env->data->surface, vec, color);
	}
}

void			display_interface(t_env *env)
{
	Uint32		color;
	t_vec		vec;
	SDL_Rect	rect;
	int			nb;
	int			i;

	// display interface area + grid
	nb = 0;
	i = 20 + env->grid_translate.x + env->grid_mouse_var.x;
	while (i < 870)
	{
		color = (nb % 5 == 0) ? 0X50FFFFFF: 0X20FFFFFF;
		vec = (t_vec){(t_pos){i, 100}, (t_pos){i, 780}};
		ui_make_line(env->data->surface, vec, color);
		i += 4 * env->pixel_value;
		nb++;
	}
	nb = 0;
	i = 100 + env->grid_translate.y + env->grid_mouse_var.y;
	while (i < 780)
	{
		color = (nb % 5 == 0) ? 0X50FFFFFF: 0X20FFFFFF;
		vec = (t_vec){(t_pos){20, i}, (t_pos){870, i}};
		ui_make_line(env->data->surface, vec, color);
		i += 4 * env->pixel_value;
		nb++;
	}
	rect = (SDL_Rect){20, 100, 850, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	display_infos(env);

	// display all edges
	t_pos	p1;
	t_pos	p2;
	t_sct	*sct;
	sct = env->sct_start;
	while (sct)
	{
		if (sct != env->sct_hover)
			display_sector(sct, env);
		sct = sct->next;
	}
	// display hovered one overflowing the others
	if (env->sct_hover)
		display_sector(env->sct_hover, env);

	// display current edge
	if (env->sct_current)
	{
		p1 = (t_pos){
		20 + env->sct_current->vtx_current->pos.x * env->pixel_value + env->grid_translate.x + env->grid_mouse_var.x,
		100 + env->sct_current->vtx_current->pos.y * env->pixel_value + env->grid_translate.y + env->grid_mouse_var.y};

		p2 = (t_pos){
		env->data->mouse.x + env->grid_translate.x + env->grid_mouse_var.x,
		env->data->mouse.y + env->grid_translate.y + env->grid_mouse_var.y};

		vec = (t_vec){p1, p2};
		ui_make_line(env->data->surface, vec, C_CYAN);
	}

	// display vtx hovering
	t_circ	circ;
	if (env->vtx_hover)
	{
		circ = (t_circ){
		20 + env->vtx_hover->pos.x * env->pixel_value + env->grid_translate.x + env->grid_mouse_var.x,
		100 + env->vtx_hover->pos.y * env->pixel_value + env->grid_translate.y + env->grid_mouse_var.y,
		10, 0xFFFFFFFF};
		ui_make_circle(circ, env->data);
	}

	// display objects
	t_object	*obj = env->objects;
	color = C_WHITE;
	while (obj)
	{
		if (obj->category == CONSUMABLE)
			color = C_GREEN;
		else if (obj->category == ENTITY)
			color = C_RED;

		p1 = (t_pos){
		20 + obj->pos.x * env->pixel_value + env->grid_translate.x + env->grid_mouse_var.x,
		100 + obj->pos.y * env->pixel_value + env->grid_translate.y + env->grid_mouse_var.y};

		rect = (SDL_Rect){p1.x - 5, p1.y - 5, 10, 10};
		ui_make_rect(env->data->surface, rect, color);
		obj = obj->next;
	}
}
