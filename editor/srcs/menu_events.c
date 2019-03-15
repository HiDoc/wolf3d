/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/15 15:02:17 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			menu_events(t_env *env)
{
	if (env->data->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
		t_square    square;

		square.rect = (t_rect){WIN_W / 2 + 10, WIN_H / 2 + 250 - 40,
		150, 25, 0xFFFFFFFF};
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, square))
		{
			env->menu.state = 0;
			return (1);
		}
	}
	return (0);
}
