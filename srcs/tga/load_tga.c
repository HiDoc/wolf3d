/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tga.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:49:14 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/27 19:49:17 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface		*tga2sur(t_tga *tga, SDL_Surface *surface)
{
	if (tga->done == NULL)
				printf("data == null\n");
	if (!(surface = SDL_CreateRGBSurfaceWithFormatFrom(&(tga->data[1]),tga->w, tga->h, 32, 4 * tga->w, SDL_PIXELFORMAT_ARGB32)))
		printf("surface fail\n");
	return (surface);
}

SDL_Surface		*load_texture(const char *path)
{
	SDL_Surface	*surface;

	surface = NULL;
	return (tga2sur(load_tga(path), surface));
}
