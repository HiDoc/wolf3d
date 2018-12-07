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
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/", filename);
	path = ft_strljoin(path, (char *)png);
	new = create_surf(path);
	free(path);
	path = NULL;
	return (new);
}

void		ak_img(t_env *env)
{
	int			count;
	char		*num;
	const char	*path = "weapons/ak_decomposee/";

	count = 2;
	env->ak_frms[0] = img_new("weapons/ak_decomposee/ak_1");
	env->ak_frms[1] = img_new("weapons/ak_decomposee/ak_02");
	while (count < 43)
	{
		num = ft_strrjoin((char *)path, ft_itoa(count + 1));
		env->ak_frms[count] = img_new(num);
		free(num);
		count++;
	}
}

void	stitch(t_env *env)
{
	int			count;
	char		*num;
	const char	*path = "enemies/stitch/";

	count = 0;
	while (count < 18)
	{
		num = ft_strrjoin((char *)path, ft_itoa(count + 1));
		env->stitch[count] = img_new(num);
		free(num);
		count++;
	}
}

void	new_bullet_surf(t_env *env)
{
	int	i;
	
	i = 1;
	while (i < 6)
	{
		env->bul_surf[i] = SDL_CreateRGBSurface(0,
						564,
						564,
						32,
						0x000000FF,
						0x0000FF00,
						0x00FF0000,
						0xFF000000);
		i++;
	}
}

void	img(t_env *env)
{
	env->walls[0] = img_new("wall_1");
	env->walls[1] = img_new("door");
	env->walls[2] = img_new("wall_1");
	env->walls[3] = img_new("wall_1");
	env->walls[4] = img_new("floor_scifi2");
	env->walls[5] = img_new("wall_1");
	env->walls[6] = img_new("floor_scifi2");
	env->walls[7] = img_new("floor_scifi2");
	env->enemy = img_new("enemy");
	env->wall = env->walls[0];
	env->floor = img_new("floor_scifi");
	env->sky = img_new("floor");
	env->gun = img_new("weapons/ak_decomposee/ak_1");
	env->life.img = img_new("thealth");
	env->lscreen.img = img_new("accueil");
	env->logo.img = img_new("logo");
	env->gun_impact = img_new("lilbullet");
	env->wobj.posters[1] = img_new("posters/lilstrangerthings");
	env->wobj.posters[2] = img_new("posters/lilstarwars");
	env->wobj.posters[3] = img_new("posters/lilbisounours");
	env->wobj.posters[4] = img_new("posters/fuckbisounours");
	env->wobj.posters[5] = img_new("posters/lildukenukem");
	ak_img(env);
	stitch(env);
	new_bullet_surf(env);
}