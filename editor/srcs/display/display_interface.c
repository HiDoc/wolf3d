/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/04 18:57:15 by sgalasso         ###   ########.fr       */
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

void			display_interface(t_env *env)
{
	Uint32		color;
	t_vec		vec;
	SDL_Rect	rect;
	int			nb;
	int			i;

	// display interface area + grid
	nb = 0;
	i = 20;
	while (i < 870)
	{
		color = (nb % 5 == 0) ? 0X50FFFFFF: 0X20FFFFFF;
		vec = (t_vec){(t_pos){i, 100}, (t_pos){i, 780}};
		ui_make_line(env->data->surface, vec, color);
		i += 4 * env->pixel_value;
		nb++;
	}
	nb = 0;
	i = 100;
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
	t_sct	*sct;
	t_vtx	*vtx;
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
		ui_make_circle(circ, env->data);
	}

	// display current edge
	if (env->sct_current)
	{
		vec = (t_vec){env->sct_current->vtx_current->pos, env->data->mouse};
		ui_make_line(env->data->surface, vec, C_CYAN);
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
		rect = (SDL_Rect){obj->pos.x - 5, obj->pos.y - 5, 10, 10};
		ui_make_rect(env->data->surface, rect, color);
		obj = obj->next;
	}
}
