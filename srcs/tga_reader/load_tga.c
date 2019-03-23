/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tga.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:35:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/23 11:03:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	tga2sur(t_tga *tga, SDL_Surface *surface)
{
	surface = SDL_CreateRGBSurfaceWithFormatFrom(tga->pxl,tga->w, tga->h, 32, 4 * tga->w, SDL_PIXELFORMAT_ARGB32);
}

void		load_texture(char *path)
{
	SDL_Surface	*surface;
	t_tga		*tga;

	surface = NULL;
	tga = NULL;
	if (!(tga = (t_tga *)malloc(sizeof(t_tga))))
		printf("Cant malloc tga\n");
	tga_load(tga, path);
	tga2sur(tga, surface);
}