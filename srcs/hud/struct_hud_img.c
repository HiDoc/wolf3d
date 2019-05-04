/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:02:07 by abaille           #+#    #+#             */
/*   Updated: 2019/05/03 18:30:22 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		img_scaled_copy(SDL_Surface *src, SDL_Surface *dst)
{
	int		x;
	int		y;
	t_vtx	scale;
	Uint32	c;

	scale = (t_vtx){fabs((float)src->w / (float)dst->w),
		fabs((float)src->h / (float)dst->h)};
	x = 0;
	while (x < dst->w)
	{
		y = 0;
		while (y < dst->h)
		{
			c = getpixel(src, (int)(x * scale.x), (int)(y * scale.y));
			if (c & 0xFF00)
				setpixel(dst, x, y, c);
			y++;
		}
		x++;
	}
}

void		draw_img(t_env *env, SDL_Surface *img, t_bloc *bloc)
{
	int			i;
	int			j;
	Uint32 		color;
	const float ratiox = img->w / (float)bloc->rect.w;
	const float ratioy = img->h / (float)bloc->rect.h;

	i = bloc->limit.v1.x;
	while (i < bloc->rect.w - bloc->limit.v2.x
	&& (ratiox > 1 ? (i * ratiox) : i) < img->w)
	{
		j = bloc->limit.v1.y;
		while (j < bloc->rect.h - bloc->limit.v2.y
		&& (ratioy > 1 ? (j * ratioy) : j) < img->h)
		{
			color = getpixel(img, (ratiox > 1 ? (i * ratiox) : i),
			(ratioy > 1 ? (j * ratioy) : j));
			if (color & 0xFF)
				setpixel(env->sdl.surface, i + bloc->rect.x,
				j + bloc->rect.y, color);
			j++;
		}
		i++;
	}
}

SDL_Surface	*ui_img(char *file, int i)
{
	SDL_Surface	*new;
	char		*nb;
	char		*path;
	char		*final_path;
	const char	*png = ".png";

	path = NULL;
	final_path = NULL;
	nb = ft_itoa(i + 1);
	path = ft_strjoin("./rsrc/img/", file);
	final_path = ft_strjoin(path, nb);
	lt_release((void**)&path);
	lt_release((void**)&nb);
	path = ft_strjoin(final_path, (char *)png);
	new = load_image(path);
	lt_release((void**)&final_path);
	lt_release((void**)&path);
	return (new);
}

