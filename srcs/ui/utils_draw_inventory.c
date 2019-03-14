/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw_inventory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:21:01 by abaille           #+#    #+#             */
/*   Updated: 2019/03/14 19:57:35 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color)
{
	int		i;
	int		j;

	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		j = edge.v1.y;
		while (j < edge.v2.y)
		{
			setpixel(surface, i, j, color);
			j++;
		}
		i++;
	}
}

int	put_img_inv(t_env *env, SDL_Surface *img, t_edge draw_limit, t_edge padding)
{
	SDL_Rect	rect;
	SDL_Surface	*new;
	Uint32		*pixls;

	(void)env;
	rect.w = draw_limit.v2.x - draw_limit.v1.x;
	rect.h = draw_limit.v2.y - draw_limit.v1.y;
	rect.y = padding.v1.x;
	rect.x = padding.v1.y;
	if (img)
	{
		if (rect.w < img->w || rect.h < img->h)
		{
			if (!(new = SDL_CreateRGBSurface(0, rect.w, rect.h, 32,
			0xff000000, 0xff0000, 0xff00, 0xff)))
				return (0);
			SDL_LockSurface(new);
			pixls = new->pixels;
			scale_img(pixls, rect, img, (t_ixy){padding.v2.x, padding.v2.y});
			SDL_UnlockSurface(new);
			// draw_img(env, draw_limit, new, (t_ixy){0, 0});
			SDL_FreeSurface(new);
			new = NULL;
		}
		// else
			// draw_img(env, draw_limit, img, (t_ixy){0, 0});
		return (1);
	}
	return (0);
}