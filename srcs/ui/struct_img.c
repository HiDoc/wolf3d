/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:02:07 by abaille           #+#    #+#             */
/*   Updated: 2019/03/12 23:42:23 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	draw_img(t_env *env, t_edge edge, SDL_Surface *img, t_ixy pxl)
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

			// if (env->player.hud.mix)
			// {
			// 	pix = mix_colors(env,
			// 		getpixel(env->sdl.surface, edge.v1.x, j),
			// 		getpixel(img, pxl.x, y), 0.8);
			// }
			// else
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
	return (1);
}

SDL_Surface		*surface_fr_png(char *path)
{
	SDL_Surface	*new;
	SDL_Surface	*tmp;

	if ((tmp = IMG_Load(path))
	&& (new = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0)))
	{
		SDL_FreeSurface(tmp);
		tmp = NULL;
		return (new);
	}
	return (NULL);
}

SDL_Surface		*img_wpn(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";
	SDL_Surface	*img;
	Uint32		*pxl;

	if ((path = ft_strjoin("./rsrc/img/weapons/", filename))
	&& (path = ft_strljoin(path, (char *)png))
	&& (img = surface_fr_png(path)))
	{
		free(path);
		if (img->w > W || img->h > H)
		{
			if (!(new = SDL_CreateRGBSurface(0, W - W / 16, H, 32,
			0xff000000, 0xff0000, 0xff00, 0xff)))
				return (NULL);
			SDL_LockSurface(new);
			pxl = new->pixels;
			scale_img(pxl, (SDL_Rect){0, 0, W - W / 16, H}, img, (t_ixy){0, 0});
			SDL_UnlockSurface(new);
			SDL_FreeSurface(img);
			return (new);
		}
		return (img);
	}
	return (NULL);
}
