/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:02:07 by abaille           #+#    #+#             */
/*   Updated: 2019/03/23 22:07:59 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			draw_img(t_env *env, SDL_Surface *img, t_ixy start, t_edge limit_img)
{
	int		y;
	int		i;
	int		sx;
	t_vtx	scale;

	if (img->w > limit_img.v2.x || img->h > limit_img.v2.y)
	{
		scale.x = fabs((float)img->w / limit_img.v2.x);
		scale.y = fabs((float)img->h / limit_img.v2.y);
	}
	else
		scale = (t_vtx){1, 1};
	sx = start.x;
	while ((start.x < sx + limit_img.v2.x) && start.x < W)
	{
		y = limit_img.v1.y;
		i = start.y;
		while ((i < start.y + limit_img.v2.y) && (i < H))
		{
			if (getpixel(img, limit_img.v1.x * scale.x, y * scale.y) & img->format->Amask)
				setpixel(env->sdl.surface, start.x, i, getpixel(img, limit_img.v1.x * scale.x, y * scale.y));
			i++;
			y++;
		}
		start.x++;
		limit_img.v1.x++;
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

