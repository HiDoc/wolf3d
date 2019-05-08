/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:42:20 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 16:44:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float	size_bar(int tmax, int datamax, int data)
{
	return ((tmax - tmax / 2.8) / datamax * data + tmax / 2.8);
}

void	check_object_stack(t_env *e, t_wrap_inv *pack, t_ixy ref)
{
	t_bloc	*b;

	b = &e->hud.objects[ref.y];
	if ((ref.y != 0 && pack[ref.y - 1].is_full)
		|| (ref.y == 0 && check_object_type(pack, ref.x, 6) > -1))
	{
		if ((SDL_BlitScaled(b->bg_fill, NULL,
				e->sdl.surface, &b->rect)) < 0)
			doom_error_exit("Doom_nukem: blit error on check_object_stack");
		if ((SDL_BlitScaled(e->world.objects[ref.x].sprite, NULL,
				e->sdl.surface, &b->rect)) < 0)
			doom_error_exit("Doom_nukem: blit error on check_object_stack");
	}
	else
	{
		if ((SDL_BlitScaled(b->bg_empty, NULL, e->sdl.surface, &b->rect)) < 0)
			doom_error_exit("Doom_nukem: blit error on check_object_stack");
	}
}
