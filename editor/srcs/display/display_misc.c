/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:32:48 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/26 14:01:26 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        display_misc(t_env *env)
{
	SDL_Rect		rect;

	// display area rect
	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// display categories
	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_OBWL, env)->rect, C_WHITE);
	ui_make_string(get_element(E_B_MISC_MUSIC, env)->rect,
		"BACKGROUND MUSIC", env->data);

	ui_make_rect(env->data->surface,
	get_element(E_B_ELM_CONS, env)->rect, C_WHITE);
	ui_make_string(get_element(E_B_MISC_SKY, env)->rect,
		"SKYBOX TEXTURE", env->data);	

	/*// up
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
	}*/
}
