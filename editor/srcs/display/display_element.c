/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/14 16:04:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_element(t_env *env)
{
	SDL_Rect		rect;

	// display area rect
	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// display categories
	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_OBWL, env)->rect, C_WHITE);
	rect = (SDL_Rect){910, 110, 0, 20};
	ui_make_string(rect, "[sprites] wall_objects", env->data);

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_CONS, env)->rect, C_WHITE);
	rect = (SDL_Rect){910, 140, 0, 20};
	ui_make_string(rect, "[sprites] consumables", env->data);

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_NTTY, env)->rect, C_WHITE);
	rect = (SDL_Rect){910, 170, 0, 20};
	ui_make_string(rect, "[sprites] entities", env->data);

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_PRFB, env)->rect, C_WHITE);
	rect = (SDL_Rect){910, 200, 0, 20};
	ui_make_string(rect, "[sectors] prefabs", env->data);

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_SPEC, env)->rect, C_WHITE);
	rect = (SDL_Rect){910, 230, 0, 20};
	ui_make_string(rect, "[sectors] specials", env->data);

	// up
	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_UP, env)->rect, C_WHITE);

	// down
	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_DOWN, env)->rect, C_WHITE);

	// display wall_texture file
	t_elem		*elem;
	int         i;

	i = 0;
	elem = env->btn_objs;
	while (elem)
	{
		if (elem->type == env->obj_mode
		&& elem->rect.y >= 330 && elem->rect.y < 700)
		{
			ui_make_full_rect(env->data->surface, elem->rect, C_GREY);;
			ui_make_string(elem->rect, elem->str, env->data);
			i++;
		}
		elem = elem->next;
	}
}
