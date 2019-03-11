/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:02:07 by abaille           #+#    #+#             */
/*   Updated: 2019/03/11 12:33:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_img(t_env *env, t_edge edge, SDL_Surface *img, t_ixy pxl)
{
	int		j;
	int		y;
	Uint32 	pix;

	SDL_LockSurface(env->sdl.surface);
	while (edge.v1.x < edge.v2.x)
	{
		y = pxl.y;
		j = edge.v1.y;
		while (j < edge.v2.y)
		{

			if (env->player.hud.mix)
			{
				pix = mix_colors(
					getpixel(env->sdl.surface, edge.v1.x, j),
					getpixel(img, pxl.x, y), 0.9, &env->player.hud.mix);
			}
			else
				pix = getpixel(img, pxl.x, y);
			if (pix & img->format->Amask)
				setpixel(env->sdl.surface, edge.v1.x, j, pix);
			j++;
			y++;
		}
		pxl.x++;
		edge.v1.x++;
	}
	SDL_UnlockSurface(env->sdl.surface);
}

SDL_Surface		*surface_fr_png(char *path)
{
	SDL_Surface	*new;
	SDL_Surface	*tmp;

	tmp = IMG_Load(path);
	if (!tmp)
	{
		printf("Error : %s\n", SDL_GetError());
		return (NULL);
	}
	new = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(tmp);
	tmp = NULL;
	return (new);
}

SDL_Surface		*img_wpn(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/weapons/", filename);
	path = ft_strljoin(path, (char *)png);
	new = surface_fr_png(path);
	free(path);
	path = NULL;
	return (new);
}
