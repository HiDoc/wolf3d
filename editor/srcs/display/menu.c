/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:47:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/14 12:25:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	left_panel(t_pos origin, t_env *env)
{
	SDL_Rect	rect;
	Uint32		color;

	// square
	rect = (SDL_Rect){origin.x, origin.y, 400, 450};
	ui_make_full_rect(env->data->surface, rect, 0x10000000);
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// create new
	rect = (SDL_Rect){origin.x + 10, origin.y + 10, 0, 25};
	ui_make_string(rect, "Create a map", env->data);
	ui_make_input(env->data->surface, get_element(M_I_NEW, env), env->data);

	// upload
	rect = (SDL_Rect){origin.x + 10, origin.y + 90, 0, 25};
	ui_make_string(rect, "Upload a map", env->data);
	rect = (SDL_Rect){origin.x + 10, origin.y + 120, 380, 320};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// up
	SDL_BlitScaled(get_element(M_B_UP, env)->image,
	0, env->data->surface, &get_element(M_B_UP, env)->rect);

	// down
	SDL_BlitScaled(get_element(M_B_DOWN, env)->image,
	0, env->data->surface, &get_element(M_B_DOWN, env)->rect);

	// display maps file
	t_elem		*elem;

	elem = env->menu.btn_maps;
	while (elem)
	{
		color = C_WHITE;
		rect = (SDL_Rect){elem->rect.x, elem->rect.y + env->menu.idx_map * 40,
		elem->rect.w, elem->rect.h};
		if (elem == env->menu.selected)
			color = C_GREEN;
		if (rect.y >= origin.y + 100 && rect.y <= origin.y + 420)
		{
			ui_make_rect(env->data->surface, rect, color);
			ui_make_string(rect, elem->str, env->data);
		}
		elem = elem->next;
	}
}

static void	right_panel(t_pos origin, t_env *env)
{
	SDL_Rect		rect;

	// square
	rect = (SDL_Rect){origin.x + 400, origin.y, 400, 450};
	ui_make_full_rect(env->data->surface, rect, 0x10000000);
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// preview
	rect = (SDL_Rect){origin.x + 410, origin.y + 10, 380, 350};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// current map
	rect = (SDL_Rect){origin.x + 420, origin.y + 10, 380, 30};
	if (env->menu.selected)
		ui_make_string(rect, env->menu.selected->str, env->data);
	else if (get_element(M_I_NEW, env)->str)
		ui_make_string(rect, get_element(M_I_NEW, env)->str, env->data);
	else
		ui_make_string(rect, env->map_name, env->data);

	// start button
	rect = (SDL_Rect){origin.x + 410, origin.y + 400, 0, 25};
	ui_make_string(rect, "Start", env->data);
	ui_make_rect(env->data->surface,
	get_element(M_B_START, env)->rect, get_element(M_B_START, env)->color);

	// Cancel button
	rect = (SDL_Rect){origin.x + 610, origin.y + 400, 0, 25};
	if (env->menu.state == 2)
	{
		ui_make_string(rect, "Cancel", env->data); 
		ui_make_rect(env->data->surface,
		get_element(M_B_CANCEL, env)->rect, get_element(M_B_CANCEL, env)->color);
	}
}

void		menu(t_env *env)
{
	SDL_Rect	rect;
	t_pos		origin;

	origin.x = WIN_W / 2 - 400;
	origin.y = WIN_H / 2 - 225;

	// display background
	rect = (SDL_Rect){0, 0, WIN_W, WIN_H};
	SDL_BlitScaled(env->menu.background, 0, env->data->surface, &rect);

	// display popup
	rect = (SDL_Rect){origin.x + 230, origin.y - 50, 0, 35};
	ui_make_string(rect, "DOOM NUKEM EDITOR", env->data);

	// display left
	left_panel(origin, env);

	// display right
	right_panel(origin, env);

	// display nb frames
	rect = (SDL_Rect){300, 20, 0, 20};
	ui_make_nbrstring(rect, env->data->nb_frames, env->data);
}
