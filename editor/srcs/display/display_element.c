/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/30 16:34:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_element(t_env *env)
{
	t_rect		rect;

	// display area rect
	rect = (t_rect){890, 100, 290, 680, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);

	// display categories
	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_OBWL, env)->rect);
	rect = (t_rect){910, 110, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sprites] wall_objects", env->data); // posters

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_CONS, env)->rect);
	rect = (t_rect){910, 140, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sprites] consumables", env->data); // gun / shield / ...

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_NTTY, env)->rect);
	rect = (t_rect){910, 170, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sprites] entities", env->data); // bots

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_PRFB, env)->rect);
	rect = (t_rect){910, 200, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sectors] prefabs", env->data); // table / rampe

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_SPEC, env)->rect);
	rect = (t_rect){910, 230, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sectors] specials", env->data); // spawn / interest / teleport

	// up
	ui_make_rect(env->data->surface, get_element(E_B_ELM_UP, env)->rect);

	// down
	ui_make_rect(env->data->surface, get_element(E_B_ELM_DOWN, env)->rect);

	// display wall_texture file
	char		**tab;
	int         y;
	int         i;
	SDL_Rect    sdlrect;
	t_pos       origin;

	origin.x = 890;
	origin.y = 250;

	i = 0;
	tab = env->wall_objects;
	if (env->obj_mode == 1)
		tab = env->consumables;
	else if (env->obj_mode == 2)
		tab = env->entities;
	else if (env->obj_mode == 3)
		tab = env->prefabs;
	else if (env->obj_mode == 4)
		tab = env->specials;
	while (tab[i])
	{
		y = origin.y + 80 + 40 * (i + env->editor.idx_wall_txtr);
		if (y >= origin.y + 80 && y < origin.y + 130 + 320)
		{
			sdlrect = (SDL_Rect){origin.x + 20, y, 200, 30};
			ui_make_full_rect(env->data->surface, sdlrect, C_GREY);
			rect = (t_rect){origin.x + 20, y, 300, 30, C_WHITE};
			ui_make_string(rect, tab[i], env->data);
		}
		i++;
	}
}
