/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:23:29 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/24 13:20:03 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	copy_sdl(t_env *env)
{
	int i;

 	i = 0;
	while (i < 800 * 600)
	{
		env->sdl.pixels[i] = (0xFF000000 | env->mlx.data[i]);
		i++;
	}
	env->sdl.surface = surface_new(env->sdl.pixels, 800, 600);
	if (env->sdl.surface == NULL)
	{
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	env->sdl.texture = SDL_CreateTextureFromSurface(env->sdl.renderer, env->sdl.surface);
	if (env->sdl.texture == NULL)
	{
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(env->sdl.surface);
	env->sdl.surface = NULL;
}

void	init_sdl(t_env *env)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env->sdl.window = SDL_CreateWindow("SDL_CreateTexture",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_RESIZABLE);
	env->sdl.renderer = SDL_CreateRenderer(env->sdl.window, -1, 0);
	copy_sdl(env);
}
