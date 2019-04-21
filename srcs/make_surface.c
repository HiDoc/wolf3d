/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:36:44 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/21 13:56:11 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface      *make_surface(int height, int width)
{
	SDL_Surface     *surface;

	if (!(surface = lt_push(SDL_CreateRGBSurface(
			0, width, height, 32, 0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
		doom_error_exit("Doom_nukem error on make_surface");
	return (surface);
}
