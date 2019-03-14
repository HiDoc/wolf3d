/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:47:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/14 18:56:42 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		menu(t_env *env)
{
	t_rect		rect;
	t_pos		origin;

	origin.x = WIN_W / 2 - 400;
	origin.y = WIN_H / 2 - 250;

	// display background
	rect = (t_rect){0, 0, WIN_W, WIN_H, 0x00000000};
	SDL_BlitScaled(env->menu.background, 0, env->data->surface,
	&((SDL_Rect){rect.x, rect.y, rect.w, rect.h}));

	// display popup
	rect = (t_rect){origin.x, origin.y, 800, 500, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	// display left
	rect = (t_rect){origin.x, origin.y, 400, 500, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	rect = (t_rect){origin.x + 10, origin.y + 10, 0, 25, C_WHITE};
 	ui_make_string(rect, "Create a map", env->data); 
	///////////////

	// display right
	rect = (t_rect){origin.x + 400, origin.y, 400, 500, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	rect = (t_rect){origin.x + 410, origin.y + 500 - 40, 0, 25, C_WHITE};
 	ui_make_string(rect, "Start", env->data); 
	////////////////
}
