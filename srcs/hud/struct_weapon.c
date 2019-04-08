/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:20:50 by abaille           #+#    #+#             */
/*   Updated: 2019/04/08 20:11:55 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Protect this area
** from null malloc
*/
int		current_sprite(t_bloc *bloc, char *file, int i)
{
	SDL_Surface	*sprite;
	Uint32		*p;

	sprite = NULL;
	if (!(sprite = ui_img(file, i))
	|| !(bloc->sprite = SDL_CreateRGBSurface(0, W, H, 32,
		0xff000000, 0xff0000, 0xff00, 0xff)))
		return (0);
	bloc->rect = (SDL_Rect){0, 0, W, H};
	bloc->limit.v1 = (t_vtx){0, 0};
	SDL_LockSurface(bloc->sprite);
	p = (Uint32*)bloc->sprite->pixels;
	scale_img(p, bloc->rect, sprite);
	SDL_UnlockSurface(bloc->sprite);
	if (sprite)
		SDL_FreeSurface(sprite);
	return (1);
}

int	thread_current_sprite(t_bloc *child, char *path, int line, int size)
{
	int	i;

	i = line;
	while (i < size)
	{
		if (!current_sprite(&child[i], path, i))
			return (0);
		i += NB_THREAD_IMG;
	}
	return (1);
}
