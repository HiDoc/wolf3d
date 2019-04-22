/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:21:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/22 15:50:02 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static SDL_Color	ui_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color = (SDL_Color){hexa >> 24, hexa >> 16, hexa >> 8, hexa};
	return (color);
}

void		ui_draw_string(SDL_Surface *dst_surface, SDL_Rect rect,
			char *text, Uint32 color, t_env *env)
{
	SDL_Surface			*surface;
	t_font				str_data;

	ft_bzero(&str_data, sizeof(t_font));
	str_data.color = ui_hex_to_rgb(color);
	str_data.str = text;
	str_data.font = env->hud.text.arial;

	surface = make_string(str_data);
	rect.w = (rect.h * surface->w) / surface->h;

	if ((SDL_BlitScaled(surface, 0, dst_surface, &rect)) < 0)
		doom_error_exit("Doom_nukem: Blit error on ui_draw_string");
	lt_release(surface);
}

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
	str_data = (t_font){data.color, (strjoin) ? strjoin : data.str, data.font, {0, 0}, 0, 0, 0};
	new = make_string(str_data);
	lt_release(strjoin);
	return (new);
}

void		draw_scaled_string(SDL_Surface *dst, t_font data, SDL_Surface *src, t_vtx pos)
{
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
	lt_release(surface);
}
