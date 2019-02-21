/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:23:29 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 13:48:32 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*surface_new(Uint32 *pixels, int width, int height)
{
	SDL_Surface	*new;

	new = SDL_CreateRGBSurfaceFrom(
			(void *)pixels,
			width,
			height,
			32,
			4 * width,
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF);
	return (new);
}

void		copy_sdl(t_env *env)
{
	if (env->sdl.surface == NULL)
	{
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	if (env->sdl.texture == NULL)
		env->sdl.texture = SDL_CreateTextureFromSurface(
			env->sdl.renderer,
			env->sdl.surface);
	else 
	{
		SDL_UpdateTexture(env->sdl.texture,
			NULL,
			env->sdl.surface->pixels,
			env->sdl.surface->pitch);
	}
	if (env->sdl.texture == NULL)
	{
		fprintf(stderr,
				"CreateTextureFromSurface failed: %s\n",
				SDL_GetError());
		exit(1);
	}
}

void		init_sdl(t_env *env)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env->sdl.window = SDL_CreateWindow("Doom Nukem",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			env->sdl.width, env->sdl.height,
			SDL_WINDOW_SHOWN);
	env->sdl.renderer = SDL_CreateRenderer(env->sdl.window, -1, 0);
}
