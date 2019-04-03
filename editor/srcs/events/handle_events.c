/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:59:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/03 21:10:48 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void     create_object(int category, t_env *env)
{
	t_object   *new;

	if (!(new = (t_object *)ft_memalloc(sizeof(t_object))))
		ui_error_exit_sdl("Editor: create object, out of memory", env->data);
	//new->ref = /**/;
	//new->sct = /**/;
	//...
	new->pos = env->data->mouse;
	new->category = category;
	if (!(env->objects))
	{
		env->objects = new;
		env->objects->next = 0;
	}
	else
	{
		new->next = env->objects;
		env->objects = new;
	}
}

int		handle_events(t_env *env)
{
	const Uint8 	*state = env->data->state;
	const SDL_Event	event = env->data->sdl.event;

	(state[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT)
		? ui_exit_sdl(env->data) : 0;

	if (env->menu.state > 0)
		return (menu_events(env));

	if (event.type == SDL_MOUSEBUTTONDOWN)
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
			else if (env->mouse_mode == 2 && env->obj_type > -1)
			{
				if (env->sct_hover)
				{
					create_object(env->obj_type, env);
				}
			}
		}
		else if (env->mouse_mode == 2)
			return (elem_mode(env));
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
					get_element(E_B_MENU, env)->rect))
			env->menu.state = 2;
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
					get_element(E_B_SAVE, env)->rect))
			export_map(env);
	}
	else if (event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y > 0)
		{
			(env->bloc_size > 20) ? env->bloc_size -= 20 : 0;
		}
		else if (event.wheel.y)
		{
			env->bloc_size += 20;
		}
	}

	if (env->data->mouse.x || env->data->mouse.y)
	{
		// targetting vertex
		target_vertex(env);

		// targetting sector
		env->sct_hover = target_sector(env->data->mouse, env);

		// targetting object
		env->obj_hover = target_object(env->data->mouse, env);

		// calc vrx distance
		if (env->sct_current)
			env->vtx_size = sqrt(
					pow(env->sct_current->vtx_current->pos.x - env->data->mouse.x, 2)
					+ pow(env->sct_current->vtx_current->pos.y - env->data->mouse.y, 2));
		return (1);
	}
	return (0);
}
