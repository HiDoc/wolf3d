/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/15 18:19:09 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			menu_events(t_env *env)
{
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		t_square    square;
		t_square    exit_cancel;

		square.rect = (t_rect){WIN_W / 2 + 10, WIN_H / 2 + 175,
		150, 25, C_WHITE};
		exit_cancel.rect = (t_rect){WIN_W / 2 + 210, WIN_H / 2 + 175,
		150, 25, C_WHITE};
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, square))
		{
			env->menu.state = 0;
			return (1);
		}
		else if (ui_mouseenter(env->data->mouse.x,
		env->data->mouse.y, exit_cancel))
		{
			if (env->menu.state == 1)
				ui_exit_sdl(env->data);
			else
				env->menu.state = 0;
			return (1);
		}
	}
	return (0);
}
