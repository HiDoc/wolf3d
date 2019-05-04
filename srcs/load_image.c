/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:35:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/04 20:00:47 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface		*load_image(char *path)
{
	SDL_Surface *new;
	SDL_Surface *tmp;

	if (!(tmp = lt_push(IMG_Load(path), srf_del)))
		 printf("IMG_Load: %s\n", IMG_GetError());
		 //doom_error_exit("Doom_nukem: load_image error");
	if (!(new = lt_push(SDL_ConvertSurfaceFormat(
			tmp, SDL_PIXELFORMAT_ARGB32, 0), srf_del)))
		doom_error_exit("Doom_nukem error on SDL_ConvertSurfaceFormat");
	lt_release((void**)&tmp);
	return (new);
}
