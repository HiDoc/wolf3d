/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:59:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/12 15:12:41 by sgalasso         ###   ########.fr       */
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
		t_square    square;
		t_square	save;

		square.rect = (t_rect){20, 100, 850, 680, 0xFFFFFFFF};
		save.rect = (t_rect){324, 30, 0, 25, 0xFFFFFFFF};
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, square))
		{ // if on interface
			if (env->mouse_mode == 0)
				return (select_mode(env));
			else if (env->mouse_mode == 1)
				return (draw_mode(env));
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
		/*if (env->cur_vrx > -1)
			env->cur_vrx_size = sqrt(
			pow(env->vertex[env->cur_vrx].pos.x - env->data->mouse.x, 2)
			+ pow(env->vertex[env->cur_vrx].pos.y - env->data->mouse.y, 2));*/
		return (1);
	}
	return (0);
}
