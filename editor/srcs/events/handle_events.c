/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:59:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/30 16:37:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		handle_events(t_env *env)
{
	// data->mouse : mouse position
	// data->state : keyboard state
	// data->sdl->event : wait event

	if (env->data->state[SDL_SCANCODE_ESCAPE]
	|| env->data->sdl.event.type == SDL_QUIT)
		ui_exit_sdl(env->data);

	if (env->menu.state > 0)
		return (menu_events(env));

	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		t_rect		rect;

		rect = (t_rect){20, 100, 850, 680, 0xFFFFFFFF};
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_MODE_SELECT, env)->rect))
		{ // button select mode
			env->mouse_mode = 0;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_MODE_DRAW, env)->rect))
		{ // button draw mode
			env->mouse_mode = 1;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_MODE_ELEM, env)->rect))
		{ // button draw mode
			env->mouse_mode = 2;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
		{ // if on interface
			if (env->mouse_mode == 0)
				return (select_mode(env));
			else if (env->mouse_mode == 1)
				return (draw_mode(env));
		}
		else if (env->mouse_mode == 2)
			return (elem_mode(env));
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_NEW, env)->rect)
		|| ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_UPLOAD, env)->rect))
			env->menu.state = 2;
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_SAVE, env)->rect))
			export_map(env);
	}
	
	if (env->data->mouse.x || env->data->mouse.y)
	{
		// targetting vertex
		target_vertex(env);

		// targetting sector
		env->sct_hover = target_sector(env->data->mouse, env);

		// calc vrx distance
		if (env->sct_current)
			env->vtx_size = sqrt(
			pow(env->sct_current->vtx_current->pos.x - env->data->mouse.x, 2)
			+ pow(env->sct_current->vtx_current->pos.y - env->data->mouse.y, 2));
		return (1);
	}
	return (0);
}
