/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:36:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/04 12:43:46 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        display_drawing(t_env *env)
{
	SDL_Rect	rect;

	// display area rect
	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// display title
	rect = (SDL_Rect){910, 110, 0, 20};
	ui_make_string(rect, "Wall texture", env->data);

	// up
	rect = (SDL_Rect){1130, 350, 20, 20};
	ui_make_rect(env->data->surface, /*get_element(M_B_UP, env)->rect*/rect, C_WHITE);

	// down
	rect = (SDL_Rect){1130, 380, 20, 20};
	ui_make_rect(env->data->surface, /*get_element(M_B_DOWN, env)->rect*/rect, C_WHITE);

	// display preview
	rect = (SDL_Rect){910, 150, 250, 150};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// display wall_texture file
	int         y;
	int         i;
	t_pos       origin;

	origin.x = 890;
	origin.y = 250;

	i = 0;
	while (env->editor.wall_txtr[i])
	{
		y = origin.y + 80 + 40 * (i /*+ var arrow*/);
		if (y >= origin.y + 80 && y < origin.y + 130 + 320)
		{
			rect = (SDL_Rect){origin.x + 20, y, 200, 30};
			ui_make_full_rect(env->data->surface, rect, C_GREY);
			rect = (SDL_Rect){origin.x + 20, y, 300, 30};
			ui_make_string(rect, env->editor.wall_txtr[i], env->data);
		}
		i++;
	}
}
