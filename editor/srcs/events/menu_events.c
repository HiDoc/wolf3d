/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/14 12:20:38 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		reset_values(t_env *env)
{
	// reset menu input new
	get_element(M_I_NEW, env)->clicked = 0;
	get_element(M_I_NEW, env)->color = C_WHITE;

	// reset menu upload
	env->menu.selected = 0;
}

static int	click_event(t_env *env)
{
	SDL_Rect		rect;
	t_elem			*obj_map = env->menu.btn_maps;
	const t_pos		m = env->data->mouse;
	const SDL_Rect	r_upload = (SDL_Rect){
	WIN_W / 2 - 400 + 10, WIN_H / 2 - 225 + 120, 350, 320};

	if (ui_mouseenter(m.x, m.y, get_element(M_B_START, env)->rect))
	{
		if (env->menu.selected)
		{
			printf("do parsing : %s\n", env->menu.selected->str);
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

	// reseting
	reset_values(env);

	if (ui_mouseenter(m.x, m.y, get_element(M_B_UP, env)->rect))
	{
		(env->menu.idx_map < 0) ? env->menu.idx_map++ : 0;
	}
	else if (ui_mouseenter(m.x, m.y, get_element(M_B_DOWN, env)->rect))
	{
		(env->menu.idx_map > -env->menu.nb_maps + 1) ? env->menu.idx_map-- : 0;
	}
	else if (ui_mouseenter(m.x, m.y, get_element(M_I_NEW, env)->rect))
	{
		get_element(M_I_NEW, env)->clicked = 1;
		get_element(M_I_NEW, env)->color = C_GREEN;
	}
	else if (ui_mouseenter(m.x, m.y, r_upload))
	{
		while (obj_map)
		{
			rect = (SDL_Rect){
			obj_map->rect.x, obj_map->rect.y + env->menu.idx_map * 40,
			obj_map->rect.w, obj_map->rect.h};
			if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
				env->menu.selected = obj_map;
			obj_map = obj_map->next;
		}
	}
	return (1);
}

static int	keydown_event(t_env *env)
{
	char				*tmp;
	char 				*key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
	env->data->sdl.event.key.keysym.scancode));
	const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;
	int					newsize;

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
			if (get_element(M_I_NEW, env)->str_max == 0)
			{
				tmp = get_element(M_I_NEW, env)->str;
				if (!(get_element(M_I_NEW, env)->str =
						ft_zstrjoin(get_element(M_I_NEW, env)->str, key)))
					ui_error_exit_sdl("Editor: Out of memory", env->data);
				free(tmp);
			}
		}
		else if (scancode == 42)
		{
			if (get_element(M_I_NEW, env)->str)
			{
				newsize = ft_strlen(get_element(M_I_NEW, env)->str) - 1;
				if (newsize > 0)
					get_element(M_I_NEW, env)->str[newsize] = 0;
				else
				{
					ft_strdel(&get_element(M_I_NEW, env)->str);
					env->map_name = "new_map";
				}
			}
		}
		return (1);
	}
	return (0);
}

int			menu_events(t_env *env)
{
	int		change;

	change = 0;
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
		(click_event(env)) ? change = 1 : 0;
	if (env->data->sdl.event.type == SDL_KEYDOWN)
		(keydown_event(env)) ? change = 1 : 0;
	return (change);
}
