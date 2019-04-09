/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:30 by abaille           #+#    #+#             */
/*   Updated: 2019/04/09 14:37:46 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			init_fonts(t_uitxt *f)
{
	if ((f->arial = TTF_OpenFont(F_ARIAL, 100))
	&& (f->doom = TTF_OpenFont(F_DOOM, 100))
	&& (f->text = TTF_OpenFont(F_TEXT, 100))
	&& (f->number = TTF_OpenFont(F_NUMB, 100)))
		return (1);
	return (0);
}

SDL_Surface	*ui_create_simple_string(t_font data)
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

int	set_inv_strings(t_env *env)
{
	const char	*string[DSCRIP_STR_INV] = {I_STRING_0, I_STRING_1, I_STRING_2, I_STRING_3, I_STRING_4,
	I_STRING_5, I_STRING_6, I_STRING_7, I_STRING_8, I_STRING_9, I_STRING_10, I_STRING_11};
	SDL_Surface	*tmp;
	t_vtx		new_size;
	int			i;

	i = -1;
	while (++i < DSCRIP_STR_INV)
	{
		if (!(tmp = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, {0, 0}, 0, -1, -1})))
			return (0);
		new_size = (t_vtx){tmp->w / (100 / (W / 50)), tmp->h / (100 / (W / 50))};
		if (!(env->hud.text.i_obj_description[i] = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
		0xff000000, 0xff0000, 0xff00, 0xff)))
			return (0);
		ui_scaled_copy(tmp, env->hud.text.i_obj_description[i]);
	}
	return (1);
}

int	set_pick_string(t_env *env)
{
	SDL_Surface	*tmp;
	t_vtx		new_size;

	tmp = NULL;
	if (!(tmp = ui_create_simple_string((t_font){WHITE,
	PICK_STRING, env->hud.text.text, {0, 0}, 0, -1, -1})))
		return (0);
	new_size = (t_vtx){tmp->w / (100 / (W / 40)), tmp->h / (100 / (W / 40))};
	if (!(env->hud.text.pick = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
	0xff000000, 0xff0000, 0xff00, 0xff)))
		return (0);
	ui_scaled_copy(tmp, env->hud.text.pick);
	return (1);
}

int			set_door_strings(t_env *env)
{
	const char	*string[2] = {STR_DOOR_0, STR_DOOR_1};
	int			i;
	SDL_Surface	*tmp;
	t_vtx		new_size;

	i = -1;
	while (++i < 2)
	{
		if (!(tmp = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, {0, 0}, 0, -1, -1})))
			return (0);
		new_size = (t_vtx){tmp->w / (100 / (W / 40)), tmp->h / (100 / (W / 40))};
		if (!(env->hud.text.doors[i] = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
		0xff000000, 0xff0000, 0xff00, 0xff)))
			return (0);
		ui_scaled_copy(tmp, env->hud.text.doors[i]);
	}
	return (1);
}

int			set_simple_strings(t_env *env, int i, int j)
{
	const char	*string[UI_NB_STRING] = {STRING_0, STRING_1, STRING_2, STRING_3, STRING_4,
	STRING_5, STRING_6, STRING_7, STRING_8, STRING_9, STRING_10, STRING_11,
	STRING_12, STRING_13, STRING_14, STRING_15,	STRING_16, STRING_17, STRING_18,
	STRING_19, STRING_20, STRING_21, STRING_22, STRING_23, STRING_24, STRING_25,
	STRING_26, STRING_27, STRING_28, STRING_29};
	TTF_Font	*font;
	SDL_Surface	*tmp;
	t_vtx		new_size;
	int	size[UI_NB_STR_INV + 1] = {W / 20, W / 34, W / 34, W / 34, W / 60, W / 44, W / 120,
	W / 120, W / 120, W / 120, W / 120, W / 40};

	while (i < UI_NB_STRING)
	{
		font = i <= T_STATS && i >= T_INVENTORY ? env->hud.text.doom : env->hud.text.text;
		if (!(tmp = ui_create_simple_string((t_font){WHITE,
		string[i], font, {0, 0}, 0, -1, -1})))
			return (0);
		if (i < HUD_NB_STRING)
			new_size = (t_vtx){tmp->w / (100 / size[UI_NB_STR_INV]), tmp->h / (100 / size[UI_NB_STR_INV])};
		else
		{
			new_size = (t_vtx){tmp->w / (100 / size[j]), tmp->h / (100 / size[j])};
			j++;
		}
		if (!(env->hud.text.string[i] = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
		0xff000000, 0xff0000, 0xff00, 0xff)))
			return (0);
		ui_scaled_copy(tmp, env->hud.text.string[i]);
		i++;
	}
	return (set_inv_strings(env) && set_pick_string(env) && set_door_strings(env));
}
