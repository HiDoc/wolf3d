/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/29 15:39:27 by sgalasso         ###   ########.fr       */
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
	rect = (t_rect){900, 110, 270, 20, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);
	rect = (t_rect){910, 110, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sprites] wall_objects", env->data); // posters
	
	rect = (t_rect){900, 140, 270, 20, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);
	rect = (t_rect){910, 140, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sprites] consumables", env->data); // gun / shield / ...

	rect = (t_rect){900, 170, 270, 20, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);
	rect = (t_rect){910, 170, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sprites] entity", env->data); // bots

	rect = (t_rect){900, 200, 270, 20, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);
	rect = (t_rect){910, 200, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sectors] prefabs", env->data); // table / rampe

	rect = (t_rect){900, 230, 270, 20, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);
	rect = (t_rect){910, 230, 0, 20, 0xffffffff};
	ui_make_string(rect, "[sectors] specials", env->data); // spawn / interest / teleport

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
