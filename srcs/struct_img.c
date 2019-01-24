/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:18:41 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/24 16:17:05 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface		*create_surf(char *path)
{
	SDL_Surface	*new;

	new = IMG_Load(path);
	if (!new)
	{
		printf("Error : %s\n", SDL_GetError());
		return (NULL);
	}
	return (new);
}

SDL_Surface		*img_new(char *filename)
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

SDL_Surface		*img_wpn(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/weapons/", filename);
	path = ft_strljoin(path, (char *)png);
	new = create_surf(path);
	free(path);
	path = NULL;
	return (new);
}

void			new_bullet_surf(t_env *env)
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

void			img(t_env *env)
{
	env->enemies[0].sprite = img_new("enemies/enemytest");
	env->life.img = img_new("thealth");
	env->wobj.posters[1] = img_new("posters/lilstrangerthings");
	env->wobj.posters[2] = img_new("posters/lilstarwars");
	env->wobj.posters[3] = img_new("posters/lilbisounours");
	env->wobj.posters[4] = img_new("posters/fuckbisounours");
	env->wobj.posters[5] = img_new("posters/lildukenukem");
	new_bullet_surf(env);
}
