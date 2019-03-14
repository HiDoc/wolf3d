/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_load_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:46:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/14 17:56:51 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

SDL_Surface		*ui_load_image(char *path, t_env *env)
{
	SDL_Surface *surface;

	if (!(surface = IMG_Load(path)))
		ui_error_exit_sdl("wolf3d: error: bad textures", env->data);
	return (surface);
}
