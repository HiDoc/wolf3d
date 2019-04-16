/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_load_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:46:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 22:32:43 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

SDL_Surface		*ui_load_image(char *path)
{
	SDL_Surface *surface;

	if (!(surface = lt_push(IMG_Load(path), srf_del)))
		ui_error_exit_sdl("wolf3d: error: bad textures");
	return (surface);
}
