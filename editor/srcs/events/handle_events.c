/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:59:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/27 15:44:54 by sgalasso         ###   ########.fr       */
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

	if (env->data->state[SDL_SCANCODE_1])
	{
		env->mouse_mode = 0;
		return (1);
	}
	else if (env->data->state[SDL_SCANCODE_2])
	{
		env->mouse_mode = 1;
		return (1);
	}

	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		t_rect		rect;
		t_rect		new;
		t_rect		upload;
		t_rect		save;

		rect = (t_rect){20, 100, 850, 680, 0xFFFFFFFF};
		new = (t_rect){20, 20, 100, 40, 0xFFFFFFFF};
		upload = (t_rect){130, 20, 125, 40, 0xFFFFFFFF};
		save = (t_rect){324, 30, 0, 25, 0xFFFFFFFF};
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
		{ // if on interface
			if (env->mouse_mode == 0)
				return (select_mode(env));
			else if (env->mouse_mode == 1)
				return (draw_mode(env));
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, new)
		|| ui_mouseenter(env->data->mouse.x, env->data->mouse.y, upload))
		{ // else if on new or upload
			env->menu.state = 2;
		}
		/*else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, save))
		{ // else if on save button
			export_map(env);
		}*/
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
