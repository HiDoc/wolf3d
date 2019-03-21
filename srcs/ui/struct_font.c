/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:30 by abaille           #+#    #+#             */
/*   Updated: 2019/03/21 13:48:58 by abaille          ###   ########.fr       */
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

int    ui_put_data(t_env *env, t_font	data)
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

int		set_simple_strings(t_env *env)
{
	if ((env->ui.string[0] = ui_create_string((t_font){WHITE, "Already full shield !",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[1] = ui_create_string((t_font){WHITE, "No shield in stock, stop crying & find some",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[2] = ui_create_string((t_font){WHITE, "Already full of life, enjoy mate !",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[3] = ui_create_string((t_font){WHITE, "No heal in stock, hang on !",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[4] = ui_create_string((t_font){WHITE, "Too greedy man.. Already full stack of this item",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[5] = ui_create_string((t_font){WHITE, "New item placed in inventory",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[6] = ui_create_string((t_font){WHITE, "Inventory full - Max 6 different items",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[7] = ui_create_string((t_font){WHITE, "Item suppressed from inventory",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[8] = ui_create_string((t_font){WHITE, "Weapon already full",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[9] = ui_create_string((t_font){WHITE, "No ammo for this weapon",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[10] = ui_create_string((t_font){WHITE, "JetPack ON",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[11] = ui_create_string((t_font){WHITE, "JetPack OFF",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.string[12] = ui_create_string((t_font){WHITE, "No JetPack here, keep looking bro !",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.t_inv[0] = ui_create_string((t_font){WHITE, "Inventory",
	env->ui.doom, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.t_inv[1] = ui_create_string((t_font){WHITE, "Weapons",
	env->ui.doom, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.t_inv[2] = ui_create_string((t_font){WHITE, "X",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1}))
	&& (env->ui.t_inv[3] = ui_create_string((t_font){WHITE, "Use",
	env->ui.text, (t_vtx){0, 0}, 0, -1, -1})))
		return (1);
	return (0);
}
