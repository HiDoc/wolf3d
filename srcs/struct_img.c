/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:18:41 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/02 18:59:48 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*create_surf(char *path)
{
	SDL_Surface* image = IMG_Load(path);
	if (!image)
	{
		printf("Erreur de chargement de l'image : %s", SDL_GetError());
		return NULL;
	}
	return (image);
}

t_img	*img_new(t_env *env, char *filename)
{
	t_img	*new;

	(void)env;
	if ((new = malloc(sizeof(t_img))) == NULL)
		return (NULL);
	new->iptr = create_surf(filename);
	new->data = (Uint32 *)new->iptr->pixels;
	new->h = new->iptr->h;
	new->w = new->iptr->w;
	return (new);
}

void	img(t_env *env)
{
	env->walls[0] = img_new(env, "./img/wall.XPM");
	env->walls[1] = img_new(env, "./img/wall_1.XPM");
	env->walls[2] = img_new(env, "./img/wall_2.XPM");
	env->walls[3] = img_new(env, "./img/wall_3.XPM");
	env->walls[4] = img_new(env, "./img/purplestone.XPM");
	env->walls[5] = img_new(env, "./img/wall_5.XPM");
	env->walls[6] = img_new(env, "./img/purplestone.XPM");
	env->walls[7] = img_new(env, "./img/purplestone.XPM");
	env->enemy = img_new(env, "./img/enemy.png");
	env->wall = env->walls[0];
	env->floor = img_new(env, "./img/floor.XPM");
	env->sky = img_new(env, "./img/floor.XPM");
	env->gun = img_new(env, "./img/gun.png");
	env->life.img = img_new(env, "./img/thealth.png");
	env->lscreen.img = img_new(env, "./img/accueil.XPM");
	env->logo.img = img_new(env, "./img/logo.XPM");
}
