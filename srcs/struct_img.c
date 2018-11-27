/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:18:41 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/04 16:56:39 by fmadura          ###   ########.fr       */
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
	return (new);
}

SDL_Surface	*img_new(char *filename)
{
	SDL_Surface	*new;
	char		*path;

	path = ft_strjoin("./rsrc/img/", filename);
	new = create_surf(path);
	free(path);
	path = NULL;
	return (new);
}

void	img(t_env *env)
{
	env->walls[0] = img_new("wall_1.png");
	env->walls[1] = img_new("door.png");
	env->walls[2] = img_new("wall_1.png");
	env->walls[3] = img_new("wall_1.png");
	env->walls[4] = img_new("floor_scifi2.png");
	env->walls[5] = img_new("wall_1.png");
	env->walls[6] = img_new("floor_scifi2.png");
	env->walls[7] = img_new("floor_scifi2.png");
	env->enemy = img_new("enemy.png");
	env->wall = env->walls[0];
	env->floor = img_new("floor_scifi.png");
	env->sky = img_new("floor.png");
	env->gun = img_new("gun.png");
	env->life.img = img_new("thealth.png");
	env->lscreen.img = img_new("accueil.jpg");
	env->logo.img = img_new("logo.png");
}
