/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 15:40:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	keydown_event(t_env *env)
{
	const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;
	char 				*key;

	key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(scancode));
	if (get_element(M_I_NEW, env)->clicked == 1)
	{
		if (scancode >= SCN_CODE_KP_MIN && scancode <= SCN_CODE_KP_MAX)
			key += 7;
		else if (scancode == SCN_CODE_SPACE)
			key = "_";
		else if (scancode >= SCN_CODE_ALPHA_MIN && scancode <= SCN_CODE_ALPHA_MAX)
			*key += 32;
		if ((scancode >= SCN_CODE_KP_MIN && scancode <= SCN_CODE_KP_MAX)
		|| (scancode >= SCN_CODE_ALPHA_MIN && scancode <= SCN_CODE_ALPHA_MAX)
		|| scancode == SCN_CODE_SPACE)
			input_add(M_I_NEW, key, env);
		else if (scancode == SCN_CODE_BACK)
		{
			if (!(input_del(M_I_NEW, env)))
				env->map_name = "new_map";
		}
		return (1);
	}
	return (0);
}

int			menu_events(t_env *env)
{
	t_pos	m = env->data->mouse;
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		// value reset
		get_element(M_I_NEW, env)->clicked = 0;

		if (ui_mouseenter(m.x, m.y, get_element(M_B_START, env)->rect))
		{
			if (get_element(M_I_NEW, env)->str)
				env->map_name = get_element(M_I_NEW, env)->str;
			env->menu.state = 0;
		}
		else if (ui_mouseenter(m.x, m.y, get_element(M_B_CANCEL, env)->rect))
			env->menu.state = 0;
		if (ui_mouseenter(m.x, m.y, get_element(M_I_NEW, env)->rect))
			get_element(M_I_NEW, env)->clicked = 1;
		return (1);
	}
	if (env->data->sdl.event.type == SDL_KEYDOWN)
		return (keydown_event(env));
	return (0);
}
