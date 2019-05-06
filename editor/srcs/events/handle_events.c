/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:59:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 01:28:29 by sgalasso         ###   ########.fr       */
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

static int		mousewheel_event(t_env *env)
{
	const SDL_Event	event = env->data->sdl.event;
	float			newscale;

	if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_R_RECT, env)->rect))
	{
		newscale = env->editor.grid_scale
			- (event.wheel.y * (env->editor.grid_scale * 0.02));
		(newscale < 2) ? newscale = 2 : 0;
		(newscale > 45) ? newscale = 45 : 0;
		env->editor.grid_scale = newscale;
		return (1);
	}
	return (0);
}

t_elem			*get_hovered_element(t_env *env)
{
	t_pos	m = env->data->mouse;
	int		i;

	i = 0;
	while (i < ENUM_END)
	{
		if (ui_mouseenter(m.x, m.y, get_element(i, env)->rect))
			return (get_element(i, env));
		i++;
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
		env->mouse.x = (m.x - rect.x - 425) / env->editor.grid_scale
			- (env->editor.grid_translate.x + env->editor.grid_mouse_var.x);
		env->mouse.y = (m.y - rect.y - 340) / env->editor.grid_scale
			- (env->editor.grid_translate.y + env->editor.grid_mouse_var.y);
	}

	// interface event
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

	if (event.type == SDL_MOUSEWHEEL)
		return (mousewheel_event(env));
	
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		reset_values(env);
		if (ui_mouseenter(m.x, m.y, get_element(E_B_SAVE, env)->rect))
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
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_MODE_SELECT, env)->rect))
			env->editor.mode = select_mode;
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_MODE_DRAW, env)->rect))
			env->editor.mode = draw_mode;
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_MODE_MOVE, env)->rect))
			env->editor.mode = move_mode;
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_MODE_ELEM, env)->rect))
			env->editor.mode = elem_mode;
	}
	return (env->editor.mode(env));
}
