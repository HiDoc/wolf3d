/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:55:08 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/26 14:46:36 by sgalasso         ###   ########.fr       */
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

void		setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	(bpp == 1) ? *p = pixel : 0;
	(bpp == 2) ? *(Uint16 *)p = pixel : 0;
	(bpp == 4) ? *(Uint32 *)p = pixel : 0;
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
	}
}

Uint32		getpixel(SDL_Surface *surface, int x, int y)
{
	int				bpp;
	Uint8			*p;
	Uint32			ret;

	SDL_LockSurface(surface);
	x = ft_abs(--x);
	y = ft_abs(--y);
	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		ret = *p;
	else if (bpp == 2)
		ret = *(Uint16 *)p;
	else if (bpp == 3)
	{
		ret = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
		(p[0] << 16 | p[1] << 8 | p[2]) : (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		ret = *(Uint32 *)p;
	else
		ret = 0;
	SDL_UnlockSurface(surface);
	return (ret);
}

void		surface_drawrect(SDL_Surface *surface,
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

void		surface_drawborder(SDL_Surface *surface,
			SDL_Rect rect, Uint32 color)
{
	t_point		a;
	t_point		b;

	a = (t_point){rect.x, rect.y};
	b = (t_point){rect.x + rect.w, rect.y};
	surface_drawline(surface, a, b, color);
	b = (t_point){rect.x, rect.y + rect.h};
	surface_drawline(surface, a, b, color);
	a = (t_point){rect.x + rect.w, rect.y + rect.h};
	b = (t_point){rect.x + rect.w, rect.y};
	surface_drawline(surface, a, b, color);
	b = (t_point){rect.x, rect.y + rect.h};
	surface_drawline(surface, a, b, color);
}

void	surface_drawline(SDL_Surface *surface,
		t_point start, t_point end, Uint32 color)
{
	
	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;
 
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1; 
	int err = (dx > dy ? dx : -dy) / 2;
	int e2 = 0;
	
	while (x0 != x1 || y0 != y1)
	{
		setpixel(surface, x0, y0, color);
		e2 = err;
		if (e2 >-dx)
		{ 
			err -= dy; 
			x0 += sx; 		
		}
		if (e2 < dy) 
		{ 
			err += dx; 
			y0 += sy; 
		}
	}
}

void	surface_drawline_limit(SDL_Surface *surface,
		t_point start, t_point end, t_limit limit, Uint32 color)
{
	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;
 
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1; 
	int err = (dx > dy ? dx : -dy) / 2;
	int e2 = 0;
	
	while (x0 != x1 || y0 != y1)
	{
		if (x0 > limit.xmin && x0 < limit.xmax && y0 > limit.ymin && y0 < limit.ymax)
			setpixel(surface, x0, y0, color);
		e2 = err;
		if (e2 >-dx)
		{ 
			err -= dy; 
			x0 += sx; 		
		}
		if (e2 < dy) 
		{ 
			err += dx; 
			y0 += sy; 
		}
	}
}
