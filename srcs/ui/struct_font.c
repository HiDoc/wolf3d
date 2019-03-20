/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:30 by abaille           #+#    #+#             */
/*   Updated: 2019/03/20 18:34:43 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_fonts(t_ui *f)
{
	if ((f->arial = TTF_OpenFont(F_ARIAL, 100))
	&& (f->doom = TTF_OpenFont(F_DOOM, 100))
	&& (f->text = TTF_OpenFont(F_TEXT, 100))
	&& (f->number = TTF_OpenFont(F_NUMB, 100)))
		return (1);
	return (0);
}

SDL_Surface	*str_join_text(t_font data)
{
	char		*strjoin;
	SDL_Surface	*new;

	strjoin = NULL;
	if (data.l > -1)
	{
		if (!(strjoin = ft_strljoin(ft_itoa(data.l), (char *)data.str)))
			return (NULL);
	}
	else if (data.r > -1)
	{
		if (!(strjoin = ft_strrjoin((char *)data.str, ft_itoa(data.r))))
			return (NULL);
	}
	if (!(new = TTF_RenderText_Shaded(data.font,
	strjoin ? strjoin : data.str, data.color, TRANSPARENT)))
		return (0);
	if (strjoin)
		free(strjoin);
	return (new);
}

int		draw_scaled_string(t_font data, SDL_Surface *src,
SDL_Surface *dst, t_vtx pos)
{
	int		x;
	int		y;
	t_vtx	new_size;
	float	ratio;
	t_vtx	scale;

	ratio = 100 / data.size;
	new_size.x = src->w / ratio;
	new_size.y = src->h / ratio;
	scale.x = src->w / new_size.x;
	scale.y = src->h / new_size.y;
	pos.x = data.pos.x;
	x = 0;
	while (pos.x < data.pos.x + new_size.x && pos.x < W)
	{
		pos.y = data.pos.y;
		y = 0;
		while (pos.y < data.pos.y + new_size.y && pos.y < H)
		{
			if (getpixel(src, (int)(x * scale.x), (int)(y * scale.y))
			& src->format->Amask)
				setpixel(dst, pos.x, pos.y, getpixel(src, (int)(x * scale.x),
				(int)(y * scale.y)));
			y++;
			pos.y++;
		}
		x++;
		pos.x++;
	}
	return (1);
}

int    ui_put_string(t_env *env, t_font	data)
{
	SDL_Surface	    *surface;
	SDL_Surface		*tmp;

	if (!(tmp = str_join_text(data)))
		return (0);
	if (!(surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0)))
		return (0);
	SDL_FreeSurface(tmp);
	tmp = NULL;
	(void)env;
	draw_scaled_string(data, surface, env->sdl.surface, (t_vtx){0, 0});
	SDL_FreeSurface(surface);
	surface = NULL;
    return (1);
}
