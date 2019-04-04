/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:59:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/04 15:00:33 by sgalasso         ###   ########.fr       */
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

int		handle_events(t_env *env)
{
	const Uint8 	*state = env->data->state;
	const SDL_Event	event = env->data->sdl.event;
	SDL_Rect		rect = (SDL_Rect){20, 100, 850, 680};

	(state[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT)
	? ui_exit_sdl(env->data) : 0;

	if (env->menu.state > 0)
		return (menu_events(env));

	if (event.type == SDL_MOUSEBUTTONDOWN)
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
			export_map(env);
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
					get_element(E_B_MODE_SELECT, env)->rect))
		{ // button select mode
			env->mouse_mode = 0;
			reset_values(env);
			get_element(E_B_MODE_SELECT, env)->color = C_GREEN;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
					get_element(E_B_MODE_MOVE, env)->rect))
		{ // button select mode
			env->mouse_mode = 3;
			reset_values(env);
			get_element(E_B_MODE_MOVE, env)->color = C_GREEN;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
					get_element(E_B_MODE_DRAW, env)->rect))
		{ // button draw mode
			env->mouse_mode = 1;
			reset_values(env);
			get_element(E_B_MODE_DRAW, env)->color = C_GREEN;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
					get_element(E_B_MODE_ELEM, env)->rect))
		{ // button draw mode
			env->mouse_mode = 2;
			reset_values(env);
			get_element(E_B_MODE_ELEM, env)->color = C_GREEN;
			return (1);
		}
	}

	if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect)
			&& event.type == SDL_MOUSEWHEEL)
	{ // in interface & scroll
		if (event.wheel.y > 0)
			(env->bloc_size > 60) ? env->bloc_size -= 10 : 0;
		else if (event.wheel.y)
			(env->bloc_size < 200) ? env->bloc_size += 10 : 0;
	}

	// targetting vertex
	target_vertex(env);

	// targetting sector
	env->sct_hover = target_sector(env->data->mouse, env);

	// targetting object
	env->obj_hover = target_object(env->data->mouse, env);

	if (env->mouse_mode == 0)
	{
		return (select_mode(env));
	}
	else if (env->mouse_mode == 1)
	{
		return (draw_mode(env));
	}
	else if (env->mouse_mode == 2)
	{
		return (elem_mode(env));
	}

	return (0);
}
