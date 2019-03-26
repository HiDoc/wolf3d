/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:30 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 11:45:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_fonts(t_uitxt *f)
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
	char				*strjoin;
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

SDL_Surface		*ui_create_string(t_font data)
{
	SDL_Surface	*tmp;
	SDL_Surface	*surface;
	int			ret;

	ret = 0;
	tmp = NULL;
	surface = NULL;
	if ((tmp = TTF_RenderText_Shaded(data.font, data.str, data.color, TRANSPARENT))
	&& (surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0)))
		ret = 1;
	if (tmp)
		SDL_FreeSurface(tmp);
	if (!ret && surface)
		SDL_FreeSurface(surface);
	if (!ret)
		return (NULL);
	return (surface);
}

int    ui_put_data(t_env *env, t_font data)
{
	SDL_Surface	*surface;
	SDL_Surface	*tmp;
	int			ret;

	ret = 0;
	tmp = NULL;
	surface = NULL;
	if ((tmp = str_join_text(data))
	&& (surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0))
	&& draw_scaled_string(data, surface, env->sdl.surface, (t_vtx){0, 0}))
		ret = 1;
	if (tmp)
		SDL_FreeSurface(tmp);
	if (surface)
		SDL_FreeSurface(surface);
	if (!ret)
		return (0);
	return (1);
}

int		set_simple_strings(t_env *env, int i, int j)
{
	const char		*string[23] = {STRING_0, STRING_1, STRING_2, STRING_3, STRING_4,
	STRING_5, STRING_6, STRING_7, STRING_8, STRING_9, STRING_10, STRING_11,
	STRING_12, STRING_13, STRING_14, STRING_15,	STRING_16, STRING_17, STRING_18,
	STRING_19, STRING_20, STRING_21, STRING_22};

	while (i < UI_NB_STRING)
	{
		if (i < UI_NB_STRING - UI_NB_STR_INV)
		{
			if (!(env->hud.text.string[i] = ui_create_string((t_font){WHITE,
			string[i], env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
				return (0);
		}
		else
		{
			if (!(env->hud.text.t_inv[j] = ui_create_string((t_font){WHITE,
			string[i], env->hud.text.doom, (t_vtx){0, 0}, 0, -1, -1})))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
