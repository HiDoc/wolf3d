/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:18:41 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/03 17:40:51 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*create_surf(char *path)
{
	SDL_Surface* new;
	
	new = IMG_Load(path);
	if (!new)
	{
		printf("Error : %s\n", SDL_GetError());
		return NULL;
	}
	printf("h: %d, w: %d, r: %u, g: %u, b: %u, a: %u, pitch : %d\n", new->h, new->w,
			new->format->Rmask,
			new->format->Gmask,
			new->format->Bmask,
			new->format->Amask,
			new->pitch);
	return (new);
}

SDL_Surface	*img_new(char *filename)
{
	return (create_surf(filename));
}

void	img(t_env *env)
{
	env->walls[0] = img_new("./img/wall.XPM");
	env->walls[1] = img_new("./img/wall_1.png");
	env->walls[2] = img_new("./img/wall_1.png");
	env->walls[3] = img_new("./img/wall_1.png");
	env->walls[4] = img_new("./img/purplestone.XPM");
	env->walls[5] = img_new("./img/wall_1.png");
	env->walls[6] = img_new("./img/purplestone.XPM");
	env->walls[7] = img_new("./img/purplestone.XPM");
	env->enemy = img_new("./img/enemy.png");
	env->wall = env->walls[0];
	env->floor = img_new("./img/floor.png");
	env->sky = img_new("./img/floor.XPM");
	env->gun = img_new("./img/gun.png");
	env->life.img = img_new("./img/thealth.png");
	env->lscreen.img = img_new("./img/accueil.XPM");
	env->logo.img = img_new("./img/logo.XPM");
}
