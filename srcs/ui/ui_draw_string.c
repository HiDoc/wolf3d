/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:21:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/21 18:04:51 by fmadura          ###   ########.fr       */
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

static SDL_Color	ui_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

void		ui_draw_string(SDL_Surface *dst_surface, SDL_Rect rect,
			char *text, Uint32 color, t_env *env)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*surface;
	SDL_Color			sdlcolor;
	t_font				str_data;

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	sdlcolor = ui_hex_to_rgb(color);
	str_data = (t_font){sdlcolor, text, env->hud.text.arial, {0, 0}, 0, 0, 0};
	surface = make_string(str_data);
	sdl_rect.w = (sdl_rect.h * surface->w) / surface->h;
	if ((SDL_BlitScaled(surface, 0, dst_surface, &sdl_rect)) < 0)
	{
		ft_putendl(SDL_GetError()); // provisoire
		exit(EXIT_FAILURE); // provisoire : rediriger erreur
	}
	lt_release(surface);
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

void		draw_scaled_string(t_env *env, t_font data, SDL_Surface *src, t_vtx pos)
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
				setpixel(env->sdl.surface, pos.x, pos.y, color);
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
	draw_scaled_string(env, data, surface, (t_vtx){0, 0});
	lt_release(surface);
}
