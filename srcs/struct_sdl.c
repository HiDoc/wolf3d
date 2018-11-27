/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:23:29 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/03 17:43:27 by fmadura          ###   ########.fr       */
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
			0x000000FF,
			0x0000FF00,
			0x00FF0000,
			0xFF000000);
	return (new);
}

void		copy_sdl(t_env *env)
{
	int			i;

	i = 0;
	(void)i;
	if (env->sdl.surface == NULL)
	{
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	if (env->sdl.texture != NULL)
		SDL_DestroyTexture(env->sdl.texture);
	env->sdl.texture = SDL_CreateTextureFromSurface(
			env->sdl.renderer,
			env->sdl.surface);
	if (env->sdl.texture == NULL)
	{
		fprintf(stderr,
				"CreateTextureFromSurface failed: %s\n",
				SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(env->sdl.surface);
	env->sdl.surface = NULL;
	health(env);
}

void		init_sdl(t_env *env)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env->sdl.renderer = NULL;
	env->sdl.texture = NULL;
	env->sdl.surface = NULL;
	env->sdl.window = NULL;
	env->sdl.window = SDL_CreateWindow("SDL_CreateTexture",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_RESIZABLE);
	env->sdl.renderer = SDL_CreateRenderer(env->sdl.window, -1, 0);
}
