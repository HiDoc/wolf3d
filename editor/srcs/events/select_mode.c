/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/02 16:00:14 by sgalasso         ###   ########.fr       */
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
	get_element(E_I_SELEC_HCEIL, env)->clicked = 0;
	get_element(E_I_SELEC_HCEIL, env)->color = C_WHITE;
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
	{
		env->editor.mouse_drag = 1;
		env->editor.obj_select = env->editor.obj_hover;
	}
	else if (env->editor.sct_hover)
	{
		env->editor.sct_select = env->editor.sct_hover;
		// height input
		if (get_element(E_I_SELEC_HCEIL, env)->str)
			lt_release((void**)&get_element(E_I_SELEC_HCEIL, env)->str);
		if (env->editor.sct_select->ceil > 0
		&& !(get_element(E_I_SELEC_HCEIL, env)->str =
		lt_push(ft_itoa(env->editor.sct_select->ceil), ft_memdel)))
			ui_error_exit_sdl("Editor: Out of memory");
		// gravity input
		if (get_element(E_I_SELEC_GRAVITY, env)->str)
			lt_release((void**)&get_element(E_I_SELEC_GRAVITY, env)->str);
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

void			make_door(int doorsize, t_pos a, t_pos b, t_env *env)
{
	float		size;
	float		scale;
	t_vec		door;
	t_pos		center;

	center = get_edge_center(a, b);

	size = pythagore(a, b);
	scale = doorsize / size;

	door.a.x = -scale * (a.x - center.x) + center.x;
	door.a.y = -scale * (a.y - center.y) + center.y;

	door.b.x = -scale * (b.x - center.x) + center.x;
	door.b.y = -scale * (b.y - center.y) + center.y;

	create_vertex(door.a, env);
	insert_w_vertex(env->editor.edg_select, env->editor.vertex, env);
	create_vertex(door.b, env);
	insert_w_vertex(env->editor.edg_select, env->editor.vertex, env);
}

int				select_mode(t_env *env)
{
	SDL_Rect		rect = get_element(E_R_RECT, env)->rect;
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;
	t_elem 			*button;

	if (env->editor.mouse_drag)
	{
		if (event.type == SDL_MOUSEBUTTONUP)
			env->editor.mouse_drag = 0;
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
		reset_values(env);
		if (ui_mouseenter(m.x, m.y, rect))
			return (select_interface_events(env));
		else if (env->editor.sct_select)
		{
			if (ui_mouseenter(m.x, m.y,
				get_element(E_I_SELEC_HCEIL, env)->rect))
			{
				get_element(E_I_SELEC_HCEIL, env)->clicked = 1;
				get_element(E_I_SELEC_HCEIL, env)->color = C_GREEN;
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_I_SELEC_GRAVITY, env)->rect))
			{
				get_element(E_I_SELEC_GRAVITY, env)->clicked = 1;
				get_element(E_I_SELEC_GRAVITY, env)->color = C_GREEN;
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_CEIL, env)->rect))
			{
				get_element(E_B_SELEC_CEIL, env)->clicked = 1;
				get_element(E_B_SELEC_SKY, env)->clicked = 0;
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_SKY, env)->rect))
			{
				get_element(E_B_SELEC_CEIL, env)->clicked = 0;
				get_element(E_B_SELEC_SKY, env)->clicked = 1;
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_CEILTX, env)->rect))
			{
				get_element(E_B_SELEC_CEILTX, env)->clicked = 1;
				get_element(E_B_SELEC_FLOORTX, env)->clicked = 0;
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_FLOORTX, env)->rect))
			{
				get_element(E_B_SELEC_FLOORTX, env)->clicked = 1;
				get_element(E_B_SELEC_CEILTX, env)->clicked = 0;
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_TX_UP, env)->rect))
			{
				if (get_element(E_B_SELEC_CEILTX, env)->clicked == 1)
					(env->editor.dropdown[DD_CEILTX].idx_element < 0)
						? env->editor.dropdown[DD_CEILTX].idx_element++ : 0;
				else if (get_element(E_B_SELEC_FLOORTX, env)->clicked == 1)
					(env->editor.dropdown[DD_FLOORTX].idx_element < 0)
						? env->editor.dropdown[DD_FLOORTX].idx_element++ : 0;
				return (1);
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_TX_DOWN, env)->rect))
			{
				if (get_element(E_B_SELEC_CEILTX, env)->clicked == 1)
					(env->editor.dropdown[DD_CEILTX].idx_element
					> -env->editor.dropdown[DD_CEILTX].nb_element + 1)
						? env->editor.dropdown[DD_CEILTX].idx_element-- : 0;
				else if (get_element(E_B_SELEC_FLOORTX, env)->clicked == 1)
					(env->editor.dropdown[DD_FLOORTX].idx_element
					> -env->editor.dropdown[DD_FLOORTX].nb_element + 1)
						? env->editor.dropdown[DD_FLOORTX].idx_element-- : 0;
				return (1);
			}
			// click music list button
			button = env->editor.dropdown[DD_CEILTX].start;
			while (button)
			{
				if (ui_mouseenter(m.x, m.y, button->rect))
				{
					env->editor.dropdown[DD_CEILTX].current->clicked = 0;
					env->editor.dropdown[DD_CEILTX].current = button;
					button->clicked = 1;
				}
				button = button->next;
			}
			// click sb_txtr list button
			button = env->editor.dropdown[DD_FLOORTX].start;
			while (button)
			{
				if (ui_mouseenter(m.x, m.y, button->rect))
				{
					env->editor.dropdown[DD_FLOORTX].current = 0;
					env->editor.dropdown[DD_FLOORTX].current = button;
					button->clicked = 1;
				}
				button = button->next;
			}
			if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
			{
				delete_sector(env->editor.sct_select, env);
				unselect_all(env);
				return (1);
			}
		}
		else if (env->editor.edg_select)
		{
			if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_SPLIT, env)->rect))
			{
				if (env->editor.edg_select->next)
				{ // normal eddge
					create_vertex(get_edge_center(
					env->editor.edg_select->vtx->pos,
						env->editor.edg_select->next->vtx->pos), env);
				}
				else
				{ // last edge
					create_vertex(get_edge_center(
					env->editor.edg_select->vtx->pos,
						env->editor.edg_select->sector->w_vtx_start->vtx->pos),
						env);
				}
				insert_w_vertex(env->editor.edg_select, env->editor.vertex, env);
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_DOOR, env)->rect))
			{
				t_vec	vec;

				vec.a = env->editor.edg_select->vtx->pos;
				vec.b = (env->editor.edg_select->next)
					? env->editor.edg_select->next->vtx->pos
					: env->editor.edg_select->sector->w_vtx_start->vtx->pos;

				if (pythagore(vec.a, vec.b) > 3)
				{
					make_door(3, vec.a, vec.b, env);
					// w_vtx.door = 1;
				}
				else
					display_error_msg("Wall too small to make a door", env);
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_FDOOR, env)->rect))
			{
				t_vec	vec;

				vec.a = env->editor.edg_select->vtx->pos;
				vec.b = (env->editor.edg_select->next)
					? env->editor.edg_select->next->vtx->pos
					: env->editor.edg_select->sector->w_vtx_start->vtx->pos;

				if (pythagore(vec.a, vec.b) > 4)
				{
					make_door(4, vec.a, vec.b, env);
					// w_vtx.door = 1;
				}
				else
					display_error_msg("Wall too small to make a final door", env);
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_M_WALL_UP, env)->rect))
			{
				(env->editor.dropdown[DD_MWALLTX].idx_element < 0)
				? env->editor.dropdown[DD_MWALLTX].idx_element++ : 0;
				return (1);
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_M_WALL_DOWN, env)->rect))
			{
				(env->editor.dropdown[DD_MWALLTX].idx_element
				> -env->editor.dropdown[DD_MWALLTX].nb_element + 1)
					? env->editor.dropdown[DD_MWALLTX].idx_element-- : 0;
				return (1);
			}
			// click music list button
			button = env->editor.dropdown[DD_MWALLTX].start;
			while (button)
			{
				if (ui_mouseenter(m.x, m.y, button->rect))
				{
					env->editor.dropdown[DD_MWALLTX].current->clicked = 0;
					env->editor.dropdown[DD_MWALLTX].current = button;
					button->clicked = 1;
				}
				button = button->next;
			}
			if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
			{
				delete_edge(env->editor.edg_select, env);
				unselect_all(env);
				return (1);
			}
		}
		else if (env->editor.obj_select)
		{
			if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
			{
				delete_object(env->editor.obj_select, env);
				unselect_all(env);
				return (1);
			}
		}
		else if (env->editor.vtx_select)
		{
			if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
			{
				delete_vertex(env->editor.vtx_select, env);
				unselect_all(env);
				return (1);
			}
		}
		else if (!env->editor.obj_select && !env->editor.sct_select
			&& !env->editor.vtx_select && !env->editor.edg_select)
		{
			if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_MUSIC, env)->rect))
			{
				get_element(E_B_SELEC_MUSIC, env)->clicked = 1;
				get_element(E_B_SELEC_SBTX, env)->clicked = 0;
			}
			else if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_SBTX, env)->rect))
			{
				get_element(E_B_SELEC_SBTX, env)->clicked = 1;
				get_element(E_B_SELEC_MUSIC, env)->clicked = 0;
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_MISC_UP, env)->rect))
			{
				if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
					(env->editor.dropdown[DD_BGAUDIO].idx_element < 0)
						? env->editor.dropdown[DD_BGAUDIO].idx_element++ : 0;
				else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
					(env->editor.dropdown[DD_SBTX].idx_element < 0)
						? env->editor.dropdown[DD_SBTX].idx_element++ : 0;
				return (1);
			}
			else if (ui_mouseenter(m.x, m.y,
				get_element(E_B_SELEC_MISC_DOWN, env)->rect))
			{
				if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
					(env->editor.dropdown[DD_BGAUDIO].idx_element
					> -env->editor.dropdown[DD_BGAUDIO].nb_element + 1)
						? env->editor.dropdown[DD_BGAUDIO].idx_element-- : 0;
				else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
					(env->editor.dropdown[DD_SBTX].idx_element
					> -env->editor.dropdown[DD_SBTX].nb_element + 1)
						? env->editor.dropdown[DD_SBTX].idx_element-- : 0;
				return (1);
			}

			// click music list button
			button = env->editor.dropdown[DD_BGAUDIO].start;
			while (button)
			{
				if (ui_mouseenter(m.x, m.y, button->rect))
				{
					env->editor.dropdown[DD_BGAUDIO].current->clicked = 0;
					env->editor.dropdown[DD_BGAUDIO].current = button;
					button->clicked = 1;
				}
				button = button->next;
			}
			// click sb_txtr list button
			button = env->editor.dropdown[DD_SBTX].start;
			while (button)
			{
				if (ui_mouseenter(m.x, m.y, button->rect))
				{
					env->editor.dropdown[DD_SBTX].current->clicked = 0;
					env->editor.dropdown[DD_SBTX].current = button;
					button->clicked = 1;
				}
				button = button->next;
			}
		}
		return (1);
	}
	else if (event.type == SDL_KEYDOWN)
		return (select_input_events(env));
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}
