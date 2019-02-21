/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:26 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 17:04:08 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
	char	life[6];
	int		count;
	int		curr_life;

	curr_life = env->player.health;
	life[5] = '\0';
	life[4] = '%';
	life[3] = ' ';
	count = 3;
	while (count > 0)
	{
		count--;
		life[count] = (curr_life % 10) + 48;
		curr_life /= 10;
	}
	ui_put_string(env, life, 65, 450);
}

int		launch_screen(t_env *env)
{
	SDL_Surface *home;

	home = img_new("ui/home");
	put_img(env, home, 0 , 0);
	copy_sdl(env);
	render_env(env);
	SDL_FreeSurface(home);
	home = NULL;
	while (1)
	{
		if (SDL_PollEvent(&env->sdl.event) > 0
			&& env->sdl.event.type != 0x1100
			&& env->sdl.event.type != 0x200)
			break;
	}
	return (1);
}
