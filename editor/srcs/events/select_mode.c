/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 01:43:25 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int		select_input_events(t_env *env)
{
		char 				*key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
		env->data->sdl.event.key.keysym.scancode));
		const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;

		if (get_element(E_I_SELEC_HCEIL, env)->clicked == 1)
		{
			if (scancode >= 89 && scancode <= 98)
			{ // numeric keypad
				key += 7;
			}
			if ((scancode >= 89 && scancode <= 98)
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

// VRTX /////////////////////////////////////////////////////////////

void		click_obj_del(t_env *env)
{
	delete_object(env->editor.obj_select, env);
}

// OBJS /////////////////////////////////////////////////////////////

void		click_vtx_del(t_env *env)
{
	delete_vertex(env->editor.vtx_select, env);
}

// SECT /////////////////////////////////////////////////////////////

void		click_sct_normal(t_env *env)
{
	if (env->editor.sct_select->type == 2)
		env->editor.oneend = 0;
	get_element(E_B_SELEC_NORMAL, env)->clicked = 1;
	env->editor.sct_select->type = 0;
}

void		click_sct_door(t_env *env)
{
	if (env->editor.sct_select->type == 2)
		env->editor.oneend = 0;
	get_element(E_B_SELEC_DOOR, env)->clicked = 1;
	env->editor.sct_select->type = 1;
}

void		click_sct_fdoor(t_env *env)
{
	get_element(E_B_SELEC_FDOOR	, env)->clicked = 1;
	if (env->editor.oneend == 1)
		display_error_msg("You can not have 2 end system", env);
	else
	{
		env->editor.oneend = 1;
		env->editor.sct_select->type = 2;
	}
}

void		click_sct_hceil(t_env *env)
{
	get_element(E_I_SELEC_HCEIL, env)->clicked = 1;
}

void		click_sct_hfloor(t_env *env)
{
	get_element(E_I_SELEC_HFLOOR, env)->clicked = 1;
}

void		click_sct_gravity(t_env *env)
{
	get_element(E_I_SELEC_GRAVITY, env)->clicked = 1;
}

void		click_sct_ceil(t_env *env)
{
	env->editor.sct_select->roof = 1;
	get_element(E_B_SELEC_CEIL, env)->clicked = 1;
	get_element(E_B_SELEC_SKY, env)->clicked = 0;
}

void		click_sct_sky(t_env *env)
{
	env->editor.sct_select->roof = 0;
	get_element(E_B_SELEC_CEIL, env)->clicked = 0;
	get_element(E_B_SELEC_SKY, env)->clicked = 1;
}

void		click_sct_del(t_env *env)
{
	delete_sector(env->editor.sct_select, env);
}

// EDGE /////////////////////////////////////////////////////////////

void			click_edg_split(t_env *env)
{
	t_pos		pos;

	pos = (env->editor.edg_select->next)
	? env->editor.edg_select->next->vtx->pos
	: env->editor.edg_select->sector->w_vtx_start->vtx->pos;
	if (pythagore(env->editor.edg_select->vtx->pos, pos) > 10)
	{
		create_vertex(
		get_edge_center(env->editor.edg_select->vtx->pos, pos), env);
		insert_w_vertex(env->editor.edg_select, env->editor.vertex, env);
	}
	else
		display_error_msg("Edge too small to be split", env);
}

void			click_edg_del(t_env *env)
{
	delete_edge(env->editor.edg_select, env);
}

// MISC /////////////////////////////////////////////////////////////

void			click_msc_miscup(t_env *env)
{
	if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
		(env->editor.dropdown[DD_BGAUDIO].idx_element < 0)
			? env->editor.dropdown[DD_BGAUDIO].idx_element++ : 0;
	else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
		(env->editor.dropdown[DD_SBTX].idx_element < 0)
			? env->editor.dropdown[DD_SBTX].idx_element++ : 0;
}

void			click_msc_miscdown(t_env *env)
{
	if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
		(env->editor.dropdown[DD_BGAUDIO].idx_element
		> -env->editor.dropdown[DD_BGAUDIO].nb_element + 1)
			? env->editor.dropdown[DD_BGAUDIO].idx_element-- : 0;
	else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
		(env->editor.dropdown[DD_SBTX].idx_element
		> -env->editor.dropdown[DD_SBTX].nb_element + 1)
			? env->editor.dropdown[DD_SBTX].idx_element-- : 0;
}

void			click_msc_music(t_env *env)
{
	get_element(E_B_SELEC_MUSIC, env)->clicked = 1;
	get_element(E_B_SELEC_SBTX, env)->clicked = 0;
}

void			click_msc_sbtx(t_env *env)
{
	get_element(E_B_SELEC_SBTX, env)->clicked = 1;
	get_element(E_B_SELEC_MUSIC, env)->clicked = 0;
}

void			click_msc_music_btn(t_env *env)
{
	if (Mix_PlayMusic(env->editor.dropdown[DD_BGAUDIO].current->audio, -1) < 0)
		ui_error_exit_sdl("Editor error on Mix_PlayMusic");
	env->editor.dropdown[DD_BGAUDIO].current->clicked = 1;
}

void			click_msc_sbtx_btn(t_env *env)
{
	env->editor.dropdown[DD_SBTX].current->clicked = 1;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

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
		// buttons
		if (env->editor.sct_hover->type == 0)
			get_element(E_B_SELEC_NORMAL, env)->clicked = 1;
		else if (env->editor.sct_hover->type == 1)
			get_element(E_B_SELEC_DOOR, env)->clicked = 1;
		else if (env->editor.sct_hover->type == 2)
			get_element(E_B_SELEC_FDOOR, env)->clicked = 1;
		if (env->editor.sct_hover->roof == 0)
			get_element(E_B_SELEC_SKY, env)->clicked = 1;
		else if (env->editor.sct_hover->roof == 1)
			get_element(E_B_SELEC_CEIL, env)->clicked = 1;
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
	{
		page = S_SCT;
	}
	else if (env->editor.edg_select)
	{
		page = S_EDG;
	}
	else if (env->editor.obj_select)
	{
		page = S_OBJ;
	}
	else if (env->editor.vtx_select)
	{
		page = S_VTX;
	}
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
				if (button->event_fc)
				{
					env->editor.dropdown[id].current->clicked = 0;
					env->editor.dropdown[id].current = button;
					button->event_fc(env);
					return ;
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
	const SDL_Event event = env->data->sdl.event;

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
