/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 17:32:09 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			menu_events(t_env *env)
{
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_START, env)->rect))
		{
			env->menu.state = 0;
			return (1);
		}
		else if (env->menu.state == 0
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_EXIT, env)->rect))
		{
			ui_exit_sdl(env->data);
			return (1);
		}
		else if (env->menu.state != 0
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_CANCEL, env)->rect))
		{
			env->menu.state = 0;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_UP, env)->rect))
		{
			(env->menu.idx_map < 0) ? env->menu.idx_map++ : 0;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(M_B_DOWN, env)->rect))
		{
			(env->menu.idx_map > -env->menu.nb_maps + 1) ? env->menu.idx_map-- : 0;
			return (1);
		}
	}
	return (0);
}
