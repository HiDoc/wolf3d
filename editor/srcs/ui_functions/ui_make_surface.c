/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_surface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:20:16 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/02 17:22:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

SDL_Surface      *ui_make_surface(int height, int width)
{
	SDL_Surface     *surface;
	Uint32          color[4];

	color[0] = 0x000000ff;
	color[1] = 0x0000ff00;
	color[2] = 0x00ff0000;
	color[3] = 0xff000000;
	if (!(surface = SDL_CreateRGBSurface(
	0, width, height, 32, color[0], color[1], color[2], color[3])))
		return (0);
	return (surface);
}
