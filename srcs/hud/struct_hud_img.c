/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:02:07 by abaille           #+#    #+#             */
/*   Updated: 2019/03/31 20:51:14 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			draw_img(t_env *env, SDL_Surface *img, t_bloc *bloc)
{
	int		i;
	int		j;

	const float ratiox = img->w / (float)bloc->rect.w;
	const float ratioy = img->h / (float)bloc->rect.h;

	i = bloc->limit.v1.x;
	while (i < bloc->rect.w - bloc->limit.v2.x && (ratiox > 1 ? (i * ratiox) : i) < img->w)
	{
		j = bloc->limit.v1.y;
		while (j < bloc->rect.h - bloc->limit.v2.y && (ratioy > 1 ? (j * ratioy) : j) < img->h)
		{
			Uint32 color = getpixel(img, (ratiox > 1 ? (i * ratiox) : i),
			(ratioy > 1 ? (j * ratioy) : j));
			if (color & 0xff)
				setpixel(env->sdl.surface, i + bloc->rect.x,
				j + bloc->rect.y, color);
			j++;
		}
		i++;
	}
	return (1);
}

int			copy_img(Uint32 *pxl, SDL_Surface *img)
{
	int	x;
	int	y;
	Uint32	*src;

	src = img->pixels;
	x = 0;
	while (x < img->w)
	{
		y = 0;
		while (y < img->h)
		{
			pxl[img->w * y + x] = src[img->w * y + x];
			y++;
		}
		x++;
	}
	return (1);
}

SDL_Surface	*surface_fr_png(char *path)
{
	SDL_Surface	*new;
	SDL_Surface	*tmp;
	Uint32		*pxl;

	new = NULL;
	if ((new = IMG_Load(path))
	&& (tmp = SDL_ConvertSurfaceFormat(new, SDL_PIXELFORMAT_RGBA32, 0)))
	{
		SDL_FreeSurface(new);
		if (!(new = SDL_CreateRGBSurface(0, tmp->w, tmp->h, 32,
		0xff000000, 0xff0000, 0xff00, 0xff)))
			return (NULL);
		SDL_LockSurface(new);
		pxl = new->pixels;
		copy_img(pxl, tmp);
		SDL_UnlockSurface(new);
		SDL_FreeSurface(tmp);
		tmp = NULL;
		return (new);
	}
	if (new)
		free(new);
	return (NULL);
}

SDL_Surface *ui_img(char *file, int i)
{
	SDL_Surface	*new;
	char		*nb;
	char		*path;
	char		*final_path;
	const char	*png = ".png";

	path = NULL;
	final_path = NULL;
	if ((nb = ft_itoa(i + 1))
	&& (path = ft_strjoin("./rsrc/img/", file))
	&& (final_path = ft_strrjoin(path, nb))
	&& (final_path = ft_strljoin(final_path, (char *)png))
	&& (new = surface_fr_png(final_path)))
		i = 1;
	else
		i = 0;
	if (path)
		free(path);
	if (final_path)
		free(final_path);
	if (!i)
        return (NULL);
	return (new);
}

