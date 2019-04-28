/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/28 13:51:31 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_dropdown_elem_list(SDL_Rect rect, t_elem *elem,
				int index, t_env *env)
{
	Uint32		color;
	SDL_Rect	box;
	int			i;

	i = 0;
	while (elem)
	{
		color = (elem->clicked == 1) ? C_GREEN : C_WHITE;
		box = (SDL_Rect){rect.x, rect.y + i * 40 + index * 40, rect.w, 25};
		if (elem->type == env->editor.obj_mode)
		{
			if (box.y >= rect.y && box.y <= rect.y + rect.h)
			{
				ui_make_rect(env->data->surface, box, color);
				ui_make_string(box, elem->str, env->data);
			}
			i++;
		}
		elem = elem->next;
	}
}

void			display_element(t_env *env)
{
	SDL_Rect		rect;

	// display area rect
	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	rect = get_element(E_B_ELM_OBWL, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "Wall objects", env->data);

	rect = get_element(E_B_ELM_CONS, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "Consumables", env->data);

	rect = get_element(E_B_ELM_NTTY, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "Entities", env->data);

	rect = get_element(E_B_ELM_PRFB, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "Prefabs", env->data);

	rect = get_element(E_B_ELM_SPEC, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "Specials", env->data);

	// up
	if ((SDL_BlitScaled(get_element(E_B_ELM_UP, env)->image,
	0, env->data->surface, &get_element(E_B_ELM_UP, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display element");
	// down
	if ((SDL_BlitScaled(get_element(E_B_ELM_DOWN, env)->image,
	0, env->data->surface, &get_element(E_B_ELM_DOWN, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display element");

	// display buttons
	rect = (SDL_Rect){900, 280, 200, 470};
	display_dropdown_elem_list(rect, env->editor.btn_objs,
		env->editor.idx_btn_obj, env);
}
