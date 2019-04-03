/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/03 22:47:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		reset_values(t_env *env)
{
	// reset menu input new
	get_element(M_I_NEW, env)->clicked = 0;
	get_element(M_I_NEW, env)->rect.color = C_WHITE;

	// reset menu upload
	env->menu.selected = 0;
}

int			menu_events(t_env *env)
{
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_START, env)->rect))
		{
			if (env->menu.selected)
			{
				// do parsing
				printf("do parsing : %s\n", env->menu.selected->str); // temporary
				exit(0); // temporary
			}
			else if (get_element(M_I_NEW, env)->str)
				env->map_name = get_element(M_I_NEW, env)->str;
			env->menu.state = 0;
		}
		else if (env->menu.state == 2
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_CANCEL, env)->rect))
		{
			env->menu.state = 0;
		}

		// reseting
		reset_values(env);

		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_UP, env)->rect))
		{
			(env->menu.idx_map < 0) ? env->menu.idx_map++ : 0;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_DOWN, env)->rect))
		{
			(env->menu.idx_map > -env->menu.nb_maps + 1) ? env->menu.idx_map-- : 0;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_I_NEW, env)->rect))
		{
			get_element(M_I_NEW, env)->clicked = 1;
			get_element(M_I_NEW, env)->rect.color = C_GREEN;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		(t_rect){WIN_W / 2 - 400 + 10, WIN_H / 2 - 225 + 120, 350, 320, C_WHITE}))
		{ // mouse in upload
			t_elem	*obj_map = env->menu.btn_maps;
			t_rect	rect;
			while (obj_map)
			{
				rect = (t_rect){
				obj_map->rect.x, obj_map->rect.y + env->menu.idx_map * 40,
				obj_map->rect.w, obj_map->rect.h, obj_map->rect.color};
				if (ui_mouseenter(
				env->data->mouse.x, env->data->mouse.y, rect))
					env->menu.selected = obj_map;
				obj_map = obj_map->next;
			}
		}
		return (1);
	}

	if (get_element(M_I_NEW, env)->clicked == 1
	&& env->data->sdl.event.type == SDL_KEYDOWN)
	{
		char *tmp;
		char *key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
		env->data->sdl.event.key.keysym.scancode));

		if (env->data->sdl.event.key.keysym.scancode >= 89
		&& env->data->sdl.event.key.keysym.scancode <= 98)
		{ // numeric keypad
			key += 7;
		}
		else if (env->data->sdl.event.key.keysym.scancode == 44)
		{ // numeric keypad
			key = "_";
		}
		else if (env->data->sdl.event.key.keysym.scancode >= 4
		&& env->data->sdl.event.key.keysym.scancode <= 29)
		{
			*key += 32;
		}
		if ((env->data->sdl.event.key.keysym.scancode >= 89
		&& env->data->sdl.event.key.keysym.scancode <= 98)
		|| (env->data->sdl.event.key.keysym.scancode >= 4
		&& env->data->sdl.event.key.keysym.scancode <= 29)
		|| (env->data->sdl.event.key.keysym.scancode >= 30
		&& env->data->sdl.event.key.keysym.scancode <= 39)
		|| env->data->sdl.event.key.keysym.scancode == 44)
		{ // alpha numeric
			if (get_element(M_I_NEW, env)->str_max == 0)
			{
				tmp = get_element(M_I_NEW, env)->str;
				if (!(get_element(M_I_NEW, env)->str =
				ft_zstrjoin(get_element(M_I_NEW, env)->str, key)))
					ui_error_exit_sdl("Editor: Out of memory", env->data);
				free(tmp);
			}
		}
		else if (env->data->sdl.event.key.keysym.scancode == 42)
		{ // backspace
			if (get_element(M_I_NEW, env)->str)
			{
				int	newsize = ft_strlen(get_element(M_I_NEW, env)->str) - 1;
				if (newsize > 0)
					get_element(M_I_NEW, env)->str[newsize] = 0;
				else
					ft_strdel(&get_element(M_I_NEW, env)->str);
			}
		}
		return (1);
	}
	return (0);
}
