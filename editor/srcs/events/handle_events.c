/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:59:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 13:50:08 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void     reset_values(t_env *env)
{
	// reset mode buttons
	get_element(E_B_MODE_SELECT, env)->color = C_WHITE;
	get_element(E_B_MODE_MOVE, env)->color = C_WHITE;
	get_element(E_B_MODE_DRAW, env)->color = C_WHITE;
	get_element(E_B_MODE_ELEM, env)->color = C_WHITE;
}

static int		click_event(t_env *env)
{
	if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
				get_element(E_B_MENU, env)->rect))
	{ // button menu
		env->menu.state = 2;
		return (1);
	}
	else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
				get_element(E_B_SAVE, env)->rect))
	{ // button save
		/*if (edge_overlap())
			display_error_msg("Export failed, edges are overlapping", env);
		else *//*if (sector_overlap(env))
			display_error_msg("Export failed, sectors are overlapping", env);
		else if (!refresh_object_sct(env))
			display_error_msg("Export failed, object out of sector", env);
		else */if (!env->editor.onespawn)
			display_error_msg("Export failed, no player spawn", env);
		else
		{
			printf("Export\n");
			export_map(env);
		}
		return (1);
	}
	else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
				get_element(E_B_MODE_SELECT, env)->rect))
	{ // button select mode
		env->editor.mouse_mode = 0;
		reset_values(env);
		get_element(E_B_MODE_SELECT, env)->color = C_GREEN;
		return (1);
	}
	else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
				get_element(E_B_MODE_MOVE, env)->rect))
	{ // button move mode
		env->editor.mouse_mode = 3;
		reset_values(env);
		get_element(E_B_MODE_MOVE, env)->color = C_GREEN;
		return (1);
	}
	else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
				get_element(E_B_MODE_DRAW, env)->rect))
	{ // button draw mode
		env->editor.mouse_mode = 1;
		reset_values(env);
		get_element(E_B_MODE_DRAW, env)->color = C_GREEN;
		return (1);
	}
	else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
				get_element(E_B_MODE_ELEM, env)->rect))
	{ // button elem mode
		env->editor.mouse_mode = 2;
		reset_values(env);
		get_element(E_B_MODE_ELEM, env)->color = C_GREEN;
		return (1);
	}
	return (0);
}

static int		mousewheel_event(t_env *env)
{
	const SDL_Event	event = env->data->sdl.event;
	float			newscale;

	if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_R_RECT, env)->rect))
	{
		newscale = env->grid_scale - (event.wheel.y * (env->grid_scale * 0.02));
		//(newscale < 6) ? newscale = 6 : 0;
		//(newscale > 150) ? newscale = 150 : 0;
		env->grid_scale = newscale;
		return (1);
	}
	return (0);
}

int				handle_events(t_env *env)
{
	const SDL_Rect		rect = get_element(E_R_RECT, env)->rect;
	t_editor			*edt = &env->editor;
	const t_pos			m = env->data->mouse;
	const Uint8 		*state = env->data->state;
	const SDL_Event		event = env->data->sdl.event;

	/* calcul relative mouse position */
	env->mouse = (t_pos){0, 0};
	if (ui_mouseenter(m.x, m.y, rect))
	{
		env->mouse.x = (m.x - rect.x - 425) / env->grid_scale
			- (env->editor.grid_translate.x + env->editor.grid_mouse_var.x);
		env->mouse.y = (m.y - rect.y - 340) / env->grid_scale
			- (env->editor.grid_translate.y + env->editor.grid_mouse_var.y);
	}

	if ((m.x || m.y) && ui_mouseenter(m.x, m.y, rect))
	{	
		edt->vtx_hover = target_vertex(env->data->mouse, env);
		edt->edg_hover = (!edt->vtx_hover)
			? target_edge(env->data->mouse, env) : 0;
		edt->obj_hover = (!edt->vtx_hover && !edt->edg_hover)
			? target_object(env->data->mouse, env) : 0;
		edt->sct_hover = (!edt->vtx_hover && !edt->edg_hover && !edt->obj_hover)
			? target_sector(env->mouse, env) : 0;
	}

	refresh_object_sct(env);

	/* quit doom_nukem */
	(state[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT) ? ui_exit_sdl() : 0;

	if (env->menu.state > 0)
		return (menu_events(env));
	else if (event.type == SDL_MOUSEBUTTONDOWN && click_event(env))
		return (1);
	else if (event.type == SDL_MOUSEWHEEL)
		return (mousewheel_event(env));
	else if (env->editor.mouse_mode == 0)
		return (select_mode(env));
	else if (env->editor.mouse_mode == 1)
		return (draw_mode(env));
	else if (env->editor.mouse_mode == 2)
		return (elem_mode(env));
	else if (env->editor.mouse_mode == 3)
		return (move_mode(env));
	return (0);
}
