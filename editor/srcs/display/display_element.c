/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/29 14:40:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_element(t_env *env)
{
	t_rect		rect;

	// display area rect
	rect = (t_rect){890, 100, 290, 680, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);

	// display categories
	// wall_objects // sprites (posters)
	// consumables // sprites (gun / ammo / shield ...)
	// bots // sprites (monsters)
	// prefabs // sector (table / plan incline)
	// specials // (spawn / interest / teleport)

	// up
	//rect = (t_rect){1130, 350, 20, 20, 0xFFFFFFFF};
	//ui_make_rect(env->data->surface, /*get_element(M_B_UP, env)->rect*/rect);

	// down
	//rect = (t_rect){1130, 380, 20, 20, 0xFFFFFFFF};
	//ui_make_rect(env->data->surface, /*get_element(M_B_DOWN, env)->rect*/rect);

	// display preview
	//rect = (t_rect){910, 150, 250, 150, 0xFFFFFFFF};
	//ui_make_rect(env->data->surface, rect);

	// display element_texture file
	/*int         y;
	int         i;
	SDL_Rect	sdlrect;
	t_pos       origin;

	origin.x = 890;
	origin.y = 250;

	i = 0;
	while (env->editor.wall_txtr[i])
	{
		y = origin.y + 80 + 40 * (i + env->editor.idx_wall_txtr);
		if (y >= origin.y + 80 && y < origin.y + 130 + 320)
		{
			sdlrect = (SDL_Rect){origin.x + 20, y, 200, 30};
			ui_make_full_rect(env->data->surface, sdlrect, C_GREY);
			rect = (t_rect){origin.x + 20, y, 300, 30, C_WHITE};
			ui_make_string(rect, env->editor.wall_txtr[i], env->data);
		}
		i++;
	}*/
}
