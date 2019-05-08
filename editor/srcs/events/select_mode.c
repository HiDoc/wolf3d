/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 14:24:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int		select_input_events(t_env *env)
{
	char 				*key;
	const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;

	key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
		env->data->sdl.event.key.keysym.scancode));
	if (get_element(E_I_SELEC_HCEIL, env)->clicked == 1)
	{
		if (scancode >= SCN_CODE_KP_MIN && scancode <= SCN_CODE_KP_MAX)
		{ // numeric keypad
			key += 7;
		}
		if ((scancode >= SCN_CODE_KP_MIN && scancode <= SCN_CODE_KP_MAX)
		|| (scancode >= 30 && scancode <= 39))
		{
			if ((input_add(E_I_SELEC_HCEIL, key, env)))
			{
				env->editor.sct_select->ceil = ft_atoi(
				get_element(E_I_SELEC_HCEIL, env)->str);
			}
		}
		else if (scancode == 42)
		{
			input_del(E_I_SELEC_HCEIL, env);
		}
		return (1);
	}
	else if (get_element(E_I_SELEC_HFLOOR, env)->clicked == 1)
	{
		if (scancode >= 89 && scancode <= 98)
		{ // numeric keypad
			key += 7;
		}
		if ((scancode >= 89 && scancode <= 98)
		|| (scancode >= 30 && scancode <= 39))
		{
			if ((input_add(E_I_SELEC_HFLOOR, key, env)))
			{
				env->editor.sct_select->floor = ft_atoi(
				get_element(E_I_SELEC_HFLOOR, env)->str);
			}
		}
		else if (scancode == 42)
		{
			input_del(E_I_SELEC_HFLOOR, env);
		}
		return (1);
	}
	else if (get_element(E_I_SELEC_GRAVITY, env)->clicked == 1)
	{
		if (scancode >= 89 && scancode <= 98)
		{ // numeric keypad
			key += 7;
		}
		if ((scancode >= 89 && scancode <= 98)
		|| (scancode >= 30 && scancode <= 39))
		{
			if ((input_add(E_I_SELEC_GRAVITY, key, env)))
			{
				env->editor.sct_select->gravity = ft_atoi(
				get_element(E_I_SELEC_GRAVITY, env)->str);
			}
		}
		else if (scancode == 42)
		{
			input_del(E_I_SELEC_GRAVITY, env);
		}
		return (1);
	}
	return (0);
}

static void		select_interface(t_env *env)
{
	if (env->editor.vtx_hover)
	{
		env->editor.mouse_drag = 1;
		env->editor.vtx_select = env->editor.vtx_hover;
	}
	else if (env->editor.edg_hover)
	{
		env->editor.edg_select = env->editor.edg_hover;
	}
	else if (env->editor.obj_hover)
	{
		env->editor.mouse_drag = 1;
		env->editor.obj_select = env->editor.obj_hover;
	}
	else if (env->editor.sct_hover)
	{
		env->editor.sct_select = env->editor.sct_hover;

		get_element(E_B_SELEC_NORMAL, env)->clicked
			= (env->editor.sct_select->type == 0) ? 1 : 0;
		get_element(E_B_SELEC_DOOR, env)->clicked
			= (env->editor.sct_select->type == 1) ? 1 : 0;
		get_element(E_B_SELEC_FDOOR , env)->clicked
			= (env->editor.sct_select->type == 2) ? 1 : 0;

		get_element(E_B_SELEC_SKY , env)->clicked
			= (env->editor.sct_select->roof == 1) ? 0 : 1;
		get_element(E_B_SELEC_CEIL , env)->clicked
			= (env->editor.sct_select->roof == 0) ? 0 : 1;

		// hceil input
		if (get_element(E_I_SELEC_HCEIL, env)->str)
			lt_release((void **)&get_element(E_I_SELEC_HCEIL, env)->str);
		if (env->editor.sct_select->ceil > 0
		&& !(get_element(E_I_SELEC_HCEIL, env)->str =
		lt_push(ft_itoa(env->editor.sct_select->ceil), ft_memdel)))
			ui_error_exit_sdl("Editor: Out of memory");
		// hfloor input
		if (get_element(E_I_SELEC_HFLOOR, env)->str)
			lt_release((void **)&get_element(E_I_SELEC_HFLOOR, env)->str);
		if (env->editor.sct_select->floor > 0
		&& !(get_element(E_I_SELEC_HFLOOR, env)->str =
		lt_push(ft_itoa(env->editor.sct_select->floor), ft_memdel)))
			ui_error_exit_sdl("Editor: Out of memory");
		// gravity input
		if (get_element(E_I_SELEC_GRAVITY, env)->str)
			lt_release((void **)&get_element(E_I_SELEC_GRAVITY, env)->str);
		if (env->editor.sct_select->gravity > 0
		&& !(get_element(E_I_SELEC_GRAVITY, env)->str =
		lt_push(ft_itoa(env->editor.sct_select->gravity), ft_memdel)))
			ui_error_exit_sdl("Editor: Out of memory");
	}
}

static void		select_panel(t_env *env)
{
	const t_pos		m = env->data->mouse;
	t_elem			*button;
	int				i;
	int				page;
	int				id;

	id = -1;
	if (env->editor.sct_select)
		page = S_SCT;
	else if (env->editor.edg_select)
		page = S_EDG;
	else if (env->editor.obj_select)
		page = S_OBJ;
	else if (env->editor.vtx_select)
		page = S_VTX;
	else
	{
		page = S_MSC;
		id = (get_element(E_B_SELEC_MUSIC, env)->clicked)
		? id = DD_BGAUDIO : DD_SBTX;
	}

	// click msc element
	i = 0;
	while (i < ENUM_END)
	{
		if (get_element(i, env)->page == page
			&& ui_mouseenter(m.x, m.y, get_element(i, env)->rect))
		{
			if (get_element(i, env)->event_fc)
				get_element(i, env)->event_fc(env);
			return ;
		}
		i++;
	}

	// click music list button
	if (id > -1)
	{
		button = env->editor.dropdown[id].start;
		while (button)
		{
			if (ui_mouseenter(m.x, m.y, button->rect))
			{
				if (button->visible == 1)
				{
					if (button->event_fc)
					{
						env->editor.dropdown[id].current->clicked = 0;
						env->editor.dropdown[id].current = button;
						button->event_fc(env);
						return ;
					}
				}
			}
			button = button->next;
		}
	}
}

int				select_mode(t_env *env)
{
	SDL_Rect		rect = get_element(E_R_RECT, env)->rect;
	const t_pos		m = env->data->mouse;
	const SDL_Event	event = env->data->sdl.event;

	if (env->editor.mouse_drag)
	{
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			env->editor.mouse_drag = 0;
		}
		else
		{
			if (env->editor.vtx_select)
			{
				env->editor.vtx_select->pos = env->mouse;
				sync_sct_minmax(env);
			}
			else if (env->editor.obj_select)
			{
				env->editor.obj_select->pos = env->mouse;
			}
		}
		return (1);
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (Mix_PlayingMusic())
		{
			Mix_HaltMusic();
		}
		if (ui_mouseenter(m.x, m.y, rect))
		{
			env->editor.obj_select = 0;
			env->editor.vtx_select = 0;
			env->editor.edg_select = 0;
			env->editor.sct_select = 0;

			select_interface(env);
		}
		else
		{
			select_panel(env);
		}
		return (1);
	}
	else if (event.type == SDL_KEYDOWN)
	{
		select_input_events(env);
		return (1);
	}
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}
