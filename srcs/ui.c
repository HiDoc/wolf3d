/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:26 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/08 14:50:08 by fmadura          ###   ########.fr       */
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
		env->player.actions.is_loading = 0;
}

void	put_gun(t_env *env)
{
	int x;
	int y;

	x = env->sdl.width - env->mitra_frms[0]->w;
	y = env->sdl.height - env->mitra_frms[0]->h;
	put_img(env, env->mitra_frms[0], x, y);
}

void	put_health(t_env *env)
{
	int x;
	int y;

	x = 22;
	y = env->sdl.height - env->life.img->h;
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
		if (SDL_PollEvent(&env->sdl.event) > 0
		&& env->sdl.event.type != 0x1100
		&& env->sdl.event.type != 0x200)
			break;
	}
}