/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:55:08 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 14:11:44 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*create_surface(char *path)
{
	SDL_Surface	*image;

	image = IMG_Load(path);
	if (!image)
	{
		printf("Error: %s", SDL_GetError());
		return (NULL);
	}
	return (image);
}

int		init_surface(t_env *env)
{
	Uint32	rmask;
	Uint32	gmask;
	Uint32	bmask;
	Uint32	amask;

	rmask = (0xff << 16);
	gmask = (0xff << 8);
	bmask = (0xff);
	amask = (0xff << 24);
	if ((env->sdl.surface = SDL_CreateRGBSurface(0, env->sdl.width,
		env->sdl.height, 32, rmask, gmask, bmask, amask)) == NULL)
		return (0);
	return (1);
}

void	surface_drawrect(SDL_Surface *surface,
			SDL_Rect rect, t_limit *limit, Uint32 color)
{
	int		i;
	int		j;

	i = 0;
	while (i < rect.h)
	{
		j = 0;
		while (j < rect.w)
		{
			if (!limit || (rect.x + j > limit->xmin && rect.x + j < limit->xmax
			&& rect.y + i > limit->ymin && rect.y + i < limit->ymax))
				setpixel(surface, rect.x + j, rect.y + i, color);
			j++;
		}
		i++;
	}
}

void	surface_drawborder(SDL_Surface *surface,
			SDL_Rect rect, Uint32 color)
{
	t_limit	l;

	l = (t_limit){rect.x, rect.x + rect.w,
		rect.y, rect.y};
	surface_drawline(surface, l, color);
	l = (t_limit){rect.x, rect.x, rect.y,
		rect.y + rect.h};
	surface_drawline(surface, l, color);
	l = (t_limit){rect.x + rect.w, rect.x + rect.w,
		rect.y + rect.h, rect.y};
	surface_drawline(surface, l, color);
	l = (t_limit){rect.x + rect.w, rect.x,
		rect.y + rect.h, rect.y + rect.h};
	surface_drawline(surface, l, color);
}

void	surface_drawline(SDL_Surface *surface,
		t_limit l, Uint32 color)
{
	t_limit	d;
	int		err;
	int		e2;

	d = (t_limit){abs(l.xmax - l.xmin), l.xmin < l.xmax ? 1 : -1,
		abs(l.ymax - l.ymin), l.ymin < l.ymax ? 1 : -1};
	err = (d.xmin > d.ymin ? d.xmin : -d.ymin) / 2;
	e2 = 0;
	while (l.xmin != l.xmax || l.ymin != l.ymax)
	{
		setpixel(surface, l.xmin, l.ymin, color);
		e2 = err;
		if (e2 > -d.xmin)
		{
			err -= d.ymin;
			l.xmin += d.xmax;
		}
		if (e2 < d.ymin)
		{
			err += d.xmin;
			l.ymin += d.ymax;
		}
	}
}

void	surface_drawline_limit(SDL_Surface *surface, t_limit l,
		t_limit limit, Uint32 color)
{
	t_limit d;
	int		err;
	int		e2;

	d = (t_limit){abs(l.xmax - l.xmin), l.xmin < l.xmax ? 1 : -1,
			abs(l.ymax - l.ymin), l.ymin < l.ymax ? 1 : -1};
	err = (d.xmin > d.ymin ? d.xmin : -d.ymin) / 2;
	e2 = 0;
	while (l.xmin != l.xmax || l.ymin != l.ymax)
	{
		if (l.xmin > limit.xmin && l.xmin < limit.xmax
				&& l.ymin > limit.ymin && l.ymin < limit.ymax)
			setpixel(surface, l.xmin, l.ymin, color);
		e2 = err;
		if (e2 > -d.xmin)
		{
			err -= d.ymin;
			l.xmin += d.xmax;
		}
		if (e2 < d.ymin)
		{
			err += d.xmin;
			l.ymin += d.ymax;
		}
	}
}
