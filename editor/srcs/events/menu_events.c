/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/02 17:49:54 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			menu_events(t_env *env)
{
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_START, env)->rect))
		{
			if (get_element(M_I_NEW, env)->str)
				env->map_name = get_element(M_I_NEW, env)->str;
			env->menu.state = 0;
			return (1);
		}
		else if (env->menu.state == 1
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_EXIT, env)->rect))
		{
			ui_exit_sdl(env->data);
			return (1);
		}
		else if (env->menu.state == 2
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_CANCEL, env)->rect))
		{
			env->menu.state = 0;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_UP, env)->rect))
		{
			(env->menu.idx_map < 0) ? env->menu.idx_map++ : 0;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_DOWN, env)->rect))
		{
			(env->menu.idx_map > -env->menu.nb_maps + 1) ? env->menu.idx_map-- : 0;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_I_NEW, env)->rect))
		{
			get_element(M_I_NEW, env)->clicked = 1;
			return (1);
		} 
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
			/*tmp = get_element(M_I_NEW, env)->str;
			if (!(get_element(M_I_NEW, env)->str =
			ft_strrem(get_element(M_I_NEW, env)->str, 1)))
				ui_error_exit_sdl("Editor: Out of memory", env->data);
			free(tmp);*/
		}
		return (1);
	}

	return (0);
}
