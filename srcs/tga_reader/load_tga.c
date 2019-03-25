/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tga.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:48:39 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/25 12:09:11 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface		*tga2sur(t_tga *tga, SDL_Surface *surface)
{
	if (tga->done == NULL)
				printf("data == null\n");
	if (!(surface = SDL_CreateRGBSurfaceWithFormatFrom(tga->pxl,tga->w, tga->h, 32, 4 * tga->w, SDL_PIXELFORMAT_ARGB32)))
		printf("surface fail\n");
	return (surface);
}

SDL_Surface		*load_texture(char *path)
{
	SDL_Surface	*surface;
	t_tga		*tga;

	surface = NULL;
	tga = NULL;
	if (!(tga = (t_tga *)malloc(sizeof(t_tga))))
		printf("Cant malloc tga\n");
	tga_load(tga, path);
	return (tga2sur(tga, surface));
//	if (!(surface))
//		printf("NULL\n");
//	printf("work\n");
//	return (surface);
}
