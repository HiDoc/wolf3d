/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:26 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/03 17:03:31 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	put_img(t_env *env, SDL_Surface *img, int x, int y)
{
	SDL_Rect	rect;

	rect.w = 128;
	rect.h = 128;
	rect.x = x;
	rect.y = y;
	if (img)
		SDL_BlitSurface(img, NULL, env->sdl.surface, &rect);
}

void	put_gun_load(t_env *env, int frame)
{
	if (frame < 36)
		put_img(env, env->mitra_frms[frame], 200, 170);
	else
		env->ld_wp = 0;
}

void	put_gun(t_env *env)
{
	int x;
	int y;

	x = 800 - env->mitra_frms[0]->w;
	y = 600 - env->mitra_frms[0]->h;
	put_img(env, env->mitra_frms[0], x, y);
}

void	put_health(t_env *env)
{
	int x;
	int y;

	x = 22;
	y = 600 - env->life.img->h;
	put_img(env, env->life.img, x, y);
}

void	hub_texture(t_env *env, t_hub *bloc, char *line, char *police)
{
	if (!(bloc->font = TTF_OpenFont(police, 20))
	|| !(bloc->surface = TTF_RenderText_Solid(bloc->font, line, bloc->color))
	|| !(bloc->texture = SDL_CreateTextureFromSurface(
		env->sdl.renderer, bloc->surface)))
	{
		fprintf(stderr, "Police error : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	TTF_CloseFont(bloc->font);
	bloc->font = NULL;
	SDL_FreeSurface(bloc->surface);
	bloc->surface = NULL;
	SDL_SetTextureAlphaMod(bloc->texture, 190);
}

void	health(t_env *env)
{
	env->life.color = (SDL_Color){44, 200, 235, 255};
	env->life.rect = (SDL_Rect){58, 475, 60, 100};
	hub_texture(env, &env->life, "90%", "rsrc/font/yorkbailehill.ttf");
}

void	launch_screen(t_env *env)
{
	env->sdl.surface = img_new("accueil");
	copy_sdl(env);
	render_env(env);
	while (1)
	{
		if (SDL_PollEvent(&env->sdl.event) > 0)
			break;
	}
}

void	turn_logo(t_env *env)
{
	int		i;

	i = 0;
	env->logo.rect = (SDL_Rect){0, 0, 200, 200};
	while (i < 89 * 89)
	{
		if (i)//env->logo.img->data[i] != 0xEEEEEE)
		{
			;//	env->sdl.pixels[i] = (0xFF000000 | env->logo.img->data[i]);
		}
		else
		{
			;//env->sdl.pixels[i] = (0x0 | env->logo.img->data[i]);
		}
		i++;
	}
	if (!(env->logo.surface = surface_new(env->sdl.pixels, 89, 89)))
	{
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	if (!(env->logo.texture = SDL_CreateTextureFromSurface(
		env->sdl.renderer, env->logo.surface)))
	{
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n"
		, SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(env->logo.surface);
	env->logo.surface = NULL;
	SDL_RenderCopyEx(env->sdl.renderer, env->logo.texture, NULL
	, &env->logo.rect, env->logo.ang, NULL, SDL_FLIP_NONE);
	env->logo.ang += 0.1;
}
