/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:02:07 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 18:45:26 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			draw_img(t_env *env, SDL_Surface *img, t_ixy start, t_edge limit_img)
{
	Uint32	src;
	int		y;
	int		i;
	int		sx;

	sx = start.x;
	while ((start.x < sx + limit_img.v2.x) && start.x < W)
	{
		y = limit_img.v1.y;
		i = start.y;
		while ((i < start.y + limit_img.v2.y) && (i < H))
		{
			src = getpixel(img, limit_img.v1.x, y);
			if (src & img->format->Amask)
				setpixel(env->sdl.surface, start.x, i, src);
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
//	SDL_Surface	*tmp;
//	Uint32		*pxl;

	new = NULL;
	if (!(new = load_texture((const char *)path)))
		printf("load_texture fail\n");
/*	if ((new = IMG_Load(path))
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
	*/
//	if (new)
//		free(new);
//	return (NULL);
	return (new);
}

SDL_Surface *ui_img(char *res, char *doss, char *ssdoss, int i)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".tga";
	char		*nb;
	char		*resolution;

	nb = NULL;
	path = NULL;
	new = NULL;
	if ((nb = ft_itoa(i + 1))
	&& (resolution = ft_strjoin("./rsrc/img_tga/", res))
	&& (path = ft_strljoin(resolution, doss))
	&& (path = ft_strljoin(path, ssdoss))
	&& (path = ft_strljoin(path, nb))
	&& (path = ft_strljoin(path, (char *)png))
	&& (new = surface_fr_png(path)))
		i = 1;
	else
		i = 0;
	printf("i = %d", i);
	if (nb)
		free(nb);
	if (path)
		free(path);
	if (!i)
        return (NULL);
	return (new);
}

