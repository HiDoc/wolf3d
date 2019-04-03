/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/03 22:48:11 by sgalasso         ###   ########.fr       */
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
	t_elem		*elem;
	SDL_Rect    sdlrect;
	int         i;

	i = 0;
	elem = env->btn_objs;
	while (elem)
	{
		if (elem->type == env->obj_mode
		&& elem->rect.y >= 330 && elem->rect.y < 700)
		{
			sdlrect = (SDL_Rect){
			elem->rect.x, elem->rect.y, elem->rect.w, elem->rect.h};
			ui_make_full_rect(env->data->surface, sdlrect, C_GREY);;
			ui_make_string(elem->rect, elem->str, env->data);
			i++;
		}
		elem = elem->next;
	}
}
