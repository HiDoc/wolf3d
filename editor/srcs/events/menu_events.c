/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/03 14:24:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		reset_values(t_env *env)
{
	// reset menu input new
	get_element(M_I_NEW, env)->clicked = 0;
	get_element(M_I_NEW, env)->color = C_WHITE;

	// reset menu upload
	if (env->menu.dropdown.current)
	{	
		env->menu.dropdown.current->clicked = 0;
		env->menu.dropdown.current = 0;
	}
}

static void	click_event(t_env *env)
{
	t_elem			*obj_map = env->menu.dropdown.start;
	const t_pos		m = env->data->mouse;
	const SDL_Rect	r_upload = (SDL_Rect){
	WIN_W / 2 - 400 + 10, WIN_H / 2 - 225 + 120, 350, 320};

	if (ui_mouseenter(m.x, m.y, get_element(M_B_START, env)->rect))
	{
		if (env->menu.dropdown.current)
		{
			printf("do parsing : %s\n", env->menu.dropdown.current->str);
			exit(0);
		}
		else if (get_element(M_I_NEW, env)->str)
		{
			env->map_name = get_element(M_I_NEW, env)->str;
		}
		env->menu.state = 0;
	}
	else if (ui_mouseenter(m.x, m.y, get_element(M_B_CANCEL, env)->rect))
	{
		env->menu.state = 0;
	}
	else if (ui_mouseenter(m.x, m.y, get_element(M_B_UP, env)->rect))
	{
		(env->menu.dropdown.idx_element < 0)
			? env->menu.dropdown.idx_element++ : 0;
	}
	else if (ui_mouseenter(m.x, m.y, get_element(M_B_DOWN, env)->rect))
	{
		(env->menu.dropdown.idx_element > -env->menu.dropdown.nb_element + 1)
			? env->menu.dropdown.idx_element-- : 0;
	}

	// reseting
	reset_values(env);

	if (ui_mouseenter(m.x, m.y, get_element(M_I_NEW, env)->rect))
	{
		get_element(M_I_NEW, env)->clicked = 1;
		get_element(M_I_NEW, env)->color = C_GREEN;
	}
	else if (ui_mouseenter(m.x, m.y, r_upload))
	{
		while (obj_map)
		{
			if (ui_mouseenter(
					env->data->mouse.x, env->data->mouse.y, obj_map->rect))
			{
				env->menu.dropdown.current = obj_map;
				obj_map->clicked = 1;
			}
			obj_map = obj_map->next;
		}
	}
}

static int	keydown_event(t_env *env)
{
	char 				*key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
	env->data->sdl.event.key.keysym.scancode));
	const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;

	if (get_element(M_I_NEW, env)->clicked == 1)
	{
		if (scancode >= 89 && scancode <= 98)
		{ // numeric keypad
			key += 7;
		}
		else if (scancode == 44)
		{ // numeric keypad
			key = "_";
		}
		else if (scancode >= 4 && scancode <= 29)
		{ // alpha
			*key += 32;
		}
		if ((scancode >= 89 && scancode <= 98)
		|| (scancode >= 4 && scancode <= 39) || scancode == 44)
		{
			input_add(M_I_NEW, key, env);
		}
		else if (scancode == 42)
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
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		click_event(env);
		return (1);
	}
	if (env->data->sdl.event.type == SDL_KEYDOWN)
	{
		if (keydown_event(env))
			return (1);
	}
	return (0);
}
