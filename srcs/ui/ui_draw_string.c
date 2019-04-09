/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:21:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/09 22:04:02 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Color	ui_hex_to_rgb(int hexa)
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

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	sdlcolor = ui_hex_to_rgb(color);
	if (!(surface = TTF_RenderText_Blended(env->hud.text.arial, text, sdlcolor)))
	{
		ft_putendl(TTF_GetError()); // provisoire
		exit(EXIT_FAILURE); // provisoire : rediriger erreur
	}
	sdl_rect.w = (sdl_rect.h * surface->w) / surface->h;
	if ((SDL_BlitScaled(surface, 0, dst_surface, &sdl_rect)) < 0)
	{
		ft_putendl(SDL_GetError()); // provisoire
		exit(EXIT_FAILURE); // provisoire : rediriger erreur
	}
	SDL_FreeSurface(surface);
}

SDL_Surface	*str_join_text(t_font data)
{
	char				*strjoin;
	SDL_Surface	*new;

	strjoin = NULL;
	if (data.l > -1)
		strjoin = ft_strljoin(ft_itoa(data.l), (char *)data.str);
	else if (data.r > -1)
		strjoin = ft_strrjoin((char *)data.str, ft_itoa(data.r));
	if (!(new = lt_push(TTF_RenderText_Shaded(data.font,
	strjoin ? strjoin : data.str, data.color, TRANSPARENT), srf_del)))
		doom_error_exit("Doom_nukem error on TTF_RenderText_Shaded");
	lt_release(strjoin);
	return (new);
}

void		draw_scaled_string(t_env *env, t_font data, SDL_Surface *src, t_vtx pos)
{
	int		x;
	int		y;
	t_vtx	new_size;
	t_vtx	scale;

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
			if (getpixel(src, (int)(x * scale.x), (int)(y * scale.y))
			& src->format->Amask)
				setpixel(env->sdl.surface, pos.x, pos.y, getpixel(src, (int)(x * scale.x),
				(int)(y * scale.y)));
			y++;
			pos.y++;
		}
		x++;
		pos.x++;
	}
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
	lt_release(src);
}

void    		ui_put_data(t_env *env, t_font data)
{
	SDL_Surface	*surface;
	SDL_Surface	*tmp;

	tmp = str_join_text(data);
	if (!(surface = lt_push(SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0), srf_del)))
		doom_error_exit("Doom_nukem error on SDL_ConvertSurfaceFormat");
	draw_scaled_string(env, data, surface, (t_vtx){0, 0});
	lt_release(tmp);
	lt_release(surface);
}
