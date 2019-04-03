/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:36:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/03 01:05:54 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        display_drawing(t_env *env)
{
	t_rect		rect;

	// display area rect
	rect = (t_rect){890, 100, 290, 680, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);

	// display title
	rect = (t_rect){910, 110, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Wall texture", env->data);

	// up
	rect = (t_rect){1130, 350, 20, 20, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, /*get_element(M_B_UP, env)->rect*/rect);

	// down
	rect = (t_rect){1130, 380, 20, 20, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, /*get_element(M_B_DOWN, env)->rect*/rect);

	// display preview
	rect = (t_rect){910, 150, 250, 150, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);

	// display wall_texture file
	int         y;
	int         i;
	SDL_Rect	sdlrect;
	t_pos       origin;

	origin.x = 890;
	origin.y = 250;

	i = 0;
	while (env->editor.wall_txtr[i])
	{
		y = origin.y + 80 + 40 * (i /*+ var arrow*/);
		if (y >= origin.y + 80 && y < origin.y + 130 + 320)
		{
			sdlrect = (SDL_Rect){origin.x + 20, y, 200, 30};
			ui_make_full_rect(env->data->surface, sdlrect, C_GREY);
			rect = (t_rect){origin.x + 20, y, 300, 30, C_WHITE};
			ui_make_string(rect, env->editor.wall_txtr[i], env->data);
		}
		i++;
	}
}
