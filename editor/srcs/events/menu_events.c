/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 19:33:08 by sgalasso         ###   ########.fr       */
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
		char *key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
		env->data->sdl.event.key.keysym.scancode)); // proteger

		if (ft_strequ(key, "Backspace"))
		{
			/*get_element(M_I_NEW, env)->str =
			ft_strsub(get_element(M_I_NEW, env)->str, // HEEEERE
			0, ft_strlen(get_element(M_I_NEW, env)->str - 2)); // proteger*/
		}
		else
		{
			get_element(M_I_NEW, env)->str =
			ft_strjoin(get_element(M_I_NEW, env)->str, key); // proteger
		}
		return (1);
	}

	return (0);
}
