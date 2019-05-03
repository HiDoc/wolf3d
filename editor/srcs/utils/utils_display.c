/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:21:23 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/03 17:30:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			display_updown(int id_up, int id_down, t_env *env)
{
	// up
	if ((SDL_BlitScaled(get_element(id_up, env)->image,
	0, env->data->surface, &get_element(id_up, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display_updown");
	// down
	if ((SDL_BlitScaled(get_element(id_down, env)->image,
	0, env->data->surface, &get_element(id_down, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display_updown");
}

void			display_labeled_input(int id, char *str, t_env *env)
{
	SDL_Rect	rect;
	t_elem		*elem;

	elem = get_element(id, env);
	(elem->clicked) ? elem->color = C_GREEN : 0;
	rect = (SDL_Rect){elem->rect.x, elem->rect.y - 35,
		elem->rect.w, elem->rect.h};
	ui_make_string(rect, str, C_WHITE, env->data);
	ui_make_input(env->data->surface, elem, env->data);
}

void			display_button(int id, char *str, t_env *env)
{
	t_elem	*elem;
	Uint32	color;

	elem = get_element(id, env);
	color = (elem->clicked) ? C_GREEN : elem->color;
	ui_make_rect(env->data->surface, elem->rect, color);
	ui_make_string(elem->rect, str, C_WHITE, env->data);
}

void		display_editor_dropdown_list(SDL_Rect rect, int dd, t_env *env)
{
	t_elem			*elem = env->editor.dropdown[dd].start;
	int				index = env->editor.dropdown[dd].idx_element;
	Uint32			color;
	int				i;

	i = 0;
	while (elem)
	{
		color = (elem->clicked == 1) ? C_GREEN : C_WHITE;
		elem->rect = (SDL_Rect){rect.x, rect.y + i * 40 + index * 40, rect.w, 25};
		if (elem->rect.y >= rect.y && elem->rect.y <= rect.y + rect.h)
		{
			ui_make_rect(env->data->surface, elem->rect, color);
			ui_make_string(elem->rect, elem->str, C_WHITE, env->data);
		}
		elem = elem->next;
		i++;
	}
}

void		display_menu_dropdown_list(SDL_Rect rect, t_env *env)
{
	t_elem			*elem = env->menu.dropdown.start;
	int				index = env->menu.dropdown.idx_element;
	Uint32			color;
	int				i;

	i = 0;
	while (elem)
	{
		color = (elem->clicked == 1) ? C_GREEN : C_WHITE;
		elem->rect = (SDL_Rect){rect.x, rect.y + i * 40 + index * 40, rect.w, 25};
		if (elem->rect.y >= rect.y && elem->rect.y <= rect.y + rect.h)
		{
			ui_make_rect(env->data->surface, elem->rect, color);
			ui_make_string(elem->rect, elem->str, C_WHITE, env->data);
		}
		elem = elem->next;
		i++;
	}
}

void		display_error_msg(char *msg, t_env *env)
{
	if (env->editor.error_msg)
		lt_release((void **)&env->editor.error_msg);
	env->editor.timestamp = time(0);
	if (!(env->editor.error_msg = lt_push(ft_strdup(msg), ft_memdel)))
		ui_error_exit_sdl("Editor: out of memory on delete_vertex");
}
