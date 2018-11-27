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

void	put_gun(t_env *env)
{
	int x = 0;
	int y = 0;

	// while (y < env->gun->h && y < 64)
	// {
	// 	x = 0;
	// 	while (x < env->gun->w && x < 64)
	// 	{
	// 		env->sdl.pixels[y * WIDTH + x] = getpixel(env->gun, x, y); 
	// 		x++;
	// 	}
	// 	y++;
	// }
	// y = 0;
	while (y < 20)
	{
		x = 0;
		while (x < 20)
		{
			if ((x == 10 || y == 10) && x != y)
				setpixel(env->sdl.surface, x + 380, y + 280, 0xFF00FF00);
				// env->sdl.pixels[800 * 300 + (y * 800 + x) + 390] = 0xFF00FF00;
			x++;
		}
		y++;
	}
}

void	put_health(t_env *env)
{
	int x = 0;
	int y = 0;

	while (y < 141)
	{
		x = 0;
		while (x < 352)
		{
			Uint32 color = getpixel(env->life.img, x, y);
			if (color & 0xFF000000)
				setpixel(env->sdl.surface, x + 22, 600 - 142 + y, color);
			x++;
		}
		y++;
	}
}

void	hub_texture(t_env *env, t_hub *bloc, char *line, char *police)
{
	if(!(bloc->font = TTF_OpenFont(police, 20))
	|| !(bloc->surface = TTF_RenderText_Solid(bloc->font, line, bloc->color))
	|| !(bloc->texture = SDL_CreateTextureFromSurface(env->sdl.renderer, bloc->surface)))
	{
		fprintf(stderr, "Police error : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	TTF_CloseFont(bloc->font);
	bloc->font = NULL;
	SDL_FreeSurface(bloc->surface);
	bloc->surface = NULL;
	SDL_SetTextureAlphaMod(bloc->texture, 190);//opacity
}

void	health(t_env *env)
{
	env->life.color = (SDL_Color){44, 200, 235, 255};
	env->life.rect = (SDL_Rect){58, 475, 60, 100};
	hub_texture(env, &env->life, "90%", "rsrc/font/yorkbailehill.ttf");
}

void	launch_screen(t_env *env)
{
	if (!(env->lscreen.texture = SDL_CreateTextureFromSurface(env->sdl.renderer, env->lscreen.img)))
	{
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(env->lscreen.surface);
	env->lscreen.surface = NULL;
	SDL_RenderCopy(env->sdl.renderer, env->lscreen.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
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
	if (!(env->logo.texture = SDL_CreateTextureFromSurface(env->sdl.renderer, env->logo.surface)))
	{
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(env->logo.surface);
	env->logo.surface = NULL;
	SDL_RenderCopyEx(env->sdl.renderer, env->logo.texture, NULL, &env->logo.rect, env->logo.ang, NULL, SDL_FLIP_NONE);
	env->logo.ang += 0.1;
}
