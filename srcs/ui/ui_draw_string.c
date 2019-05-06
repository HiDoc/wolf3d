/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:21:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 01:20:20 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ui_scaled_copy(SDL_Surface *src, SDL_Surface *dst)
{
	int		x;
	int		y;
	t_vtx	scale;

	scale = (t_vtx){src->w / dst->w, src->h / dst->h};
	x = 0;
	while (x < dst->w)
	{
		y = 0;
		while (y < dst->h)
		{
			if (getpixel(src, (int)(x * scale.x), (int)(y * scale.y))
			& src->format->Amask)
				setpixel(dst, x, y, getpixel(src, (int)(x * scale.x),
				(int)(y * scale.y)));
			y++;
		}
		x++;
	}
}

SDL_Surface	*str_join_text(t_font data)
{
	char				*strjoin;
	SDL_Surface			*new;
	t_font				str_data;

	strjoin = NULL;
	if (data.l > -1)
		strjoin = ft_strljoin(ft_itoa(data.l), (char *)data.str);
	else if (data.r > -1)
		strjoin = ft_strrjoin((char *)data.str, ft_itoa(data.r));
	str_data = (t_font){data.color,
	(strjoin) ? strjoin : data.str, data.font, {0, 0}, 0, 0, 0};
	new = make_string(str_data);
	lt_release((void**)&strjoin);
	return (new);
}

void		draw_scaled_string(SDL_Surface *dst, t_font data, SDL_Surface *src, t_vtx pos)
{
	/*if ((SDL_BlitScaled(src, 0, dst, &rect)) < 0)
		doom_error_exit("Libui: blit error in draw_scaled_string");
*/
	int		x;
	int		y;
	t_vtx	new_size;
	t_vtx	scale;
	Uint32	color;

	new_size = (t_vtx){src->w / (100 / data.size), src->h / (100 / data.size)};
	scale = (t_vtx){src->w / new_size.x, src->h / new_size.y};
	x = 0;
	pos.x = data.pos.x;
	while (pos.x < data.pos.x + new_size.x && pos.x < W)
	{
		y = 0;
		pos.y = data.pos.y;
		while (pos.y < data.pos.y + new_size.y && pos.y < H)
		{
			color = getpixel(src, (int)(x * scale.x), (int)(y * scale.y));
			if (((color & 0xFF00) >> 8) != 42)
				setpixel(dst, pos.x, pos.y, color);
			y++;
			pos.y++;
		}
		x++;
		pos.x++;
	}


}

void    		ui_put_data(t_env *env, t_font data)
{
	SDL_Surface	*surface;

	surface = str_join_text(data);
	draw_scaled_string(env->sdl.surface, data, surface, (t_vtx){0, 0});
	lt_release((void**)&surface);
}
