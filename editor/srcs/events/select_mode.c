/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 16:07:34 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		unselect_all(t_env *env)
{
	env->editor.obj_select = 0;
	env->editor.vtx_select = 0;
	env->editor.edg_select = 0;
	env->editor.sct_select = 0;
}

static void     reset_values(t_env *env)
{
	// reset menu input new
	get_element(E_I_SELEC_HEIGHT, env)->clicked = 0;
	get_element(E_I_SELEC_HEIGHT, env)->color = C_WHITE;
}

static int		select_interface_events(t_env *env)
{
	unselect_all(env);
	if (env->editor.vtx_hover)
	{
		env->editor.mouse_drag = 1;
		env->editor.vtx_select = env->editor.vtx_hover;
	}
	else if (env->editor.edg_hover)
		env->editor.edg_select = env->editor.edg_hover;
	else if (env->editor.obj_hover)
		env->editor.obj_select = env->editor.obj_hover;
	else if (env->editor.sct_hover)
	{
		env->editor.sct_select = env->editor.sct_hover;
		// height input
		if (get_element(E_I_SELEC_HEIGHT, env)->str)
			lt_release(get_element(E_I_SELEC_HEIGHT, env)->str);
		if (env->editor.sct_select->height > 0
		&& !(get_element(E_I_SELEC_HEIGHT, env)->str =
		lt_push(ft_itoa(env->editor.sct_select->height), ft_memdel)))
			ui_error_exit_sdl("Editor: Out of memory");
		// gravity input
		if (get_element(E_I_SELEC_GRAVITY, env)->str)
			lt_release(get_element(E_I_SELEC_GRAVITY, env)->str);
		if (env->editor.sct_select->gravity > 0
		&& !(get_element(E_I_SELEC_GRAVITY, env)->str =
		lt_push(ft_itoa(env->editor.sct_select->gravity), ft_memdel)))
			ui_error_exit_sdl("Editor: Out of memory");
	}
	return (1);
}

static int		select_input_events(t_env *env)
{
		char 				*key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
		env->data->sdl.event.key.keysym.scancode));
		const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;

		if (get_element(E_I_SELEC_HEIGHT, env)->clicked == 1)
		{
			if (scancode >= 89 && scancode <= 98)
			{ // numeric keypad
				key += 7;
			}
			if ((scancode >= 89 && scancode <= 98)
			|| (scancode >= 30 && scancode <= 39))
			{
				if ((input_add(E_I_SELEC_HEIGHT, key, env)))
				{
					env->editor.sct_select->height = ft_atoi(
					get_element(E_I_SELEC_HEIGHT, env)->str);
				}
			}
			else if (scancode == 42)
			{
				input_del(E_I_SELEC_HEIGHT, env);
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

int				select_mode(t_env *env)
{
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect  rect = (SDL_Rect){20, 100, 850, 680};

	if (env->editor.mouse_drag)
	{
		if (event.type == SDL_MOUSEBUTTONUP)
			env->editor.mouse_drag = 0;
		else
		{
			env->editor.vtx_select->pos = env->mouse;
			sync_sct_minmax(env);
		}
		return (1);
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		reset_values(env);
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
			return (select_interface_events(env));
		else if (env->editor.sct_select
		&& ui_mouseenter(m.x, m.y, get_element(E_I_SELEC_HEIGHT, env)->rect))
		{
			get_element(E_I_SELEC_HEIGHT, env)->clicked = 1;
			get_element(E_I_SELEC_HEIGHT, env)->color = C_GREEN;
		}
		else if (env->editor.sct_select
		&& ui_mouseenter(m.x, m.y, get_element(E_I_SELEC_GRAVITY, env)->rect))
		{
			get_element(E_I_SELEC_GRAVITY, env)->clicked = 1;
			get_element(E_I_SELEC_GRAVITY, env)->color = C_GREEN;
		}
		else if (env->editor.edg_select
		&& ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_SPLIT, env)->rect))
		{
			create_vertex(get_edge_center(env->editor.edg_select->vtx->pos,
				env->editor.edg_select->next->vtx->pos), env);
			insert_w_vertex(env->editor.edg_select, env->vertex, env);
		}
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
		{
			if (env->editor.obj_select)
				delete_object(env->editor.obj_select, env);
			else if (env->editor.sct_select)
				delete_sector(env->editor.sct_select, env);
			else if (env->editor.vtx_select)
				delete_vertex(env->editor.vtx_select, env);
			unselect_all(env);
			return (1);	
		}
		return (0);
	}
	else if (event.type == SDL_KEYDOWN)
		return (select_input_events(env));
	else if (env->data->mouse.x || env->data->mouse.y)
		return (1);
	return (0);
}
