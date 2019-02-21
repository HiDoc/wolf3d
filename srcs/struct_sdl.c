/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:23:29 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 16:37:35 by fmadura          ###   ########.fr       */
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

int			init_sdl(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		"Couldn't initialize SDL: %s", SDL_GetError());
		return (0);
	}
	if (TTF_Init() < 0)
	{
		fprintf(stderr, "init TTF failed: %s\n", SDL_GetError());
		return (0);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env->sdl.window = SDL_CreateWindow("Doom Nukem",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			env->sdl.width, env->sdl.height,
			SDL_WINDOW_SHOWN);
	if (env->sdl.window == NULL)
		return (0);
	env->sdl.renderer = SDL_CreateRenderer(env->sdl.window, -1, SDL_RENDERER_SOFTWARE);
	if (env->sdl.renderer == NULL)
		return (0);
	SDL_SetRenderTarget(env->sdl.renderer, env->sdl.texture);
	return (1);
}
