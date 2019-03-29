/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:30 by abaille           #+#    #+#             */
/*   Updated: 2019/03/29 17:10:56 by abaille          ###   ########.fr       */
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
	const char	*string[12] = {I_STRING_0, I_STRING_1, I_STRING_2, I_STRING_3, I_STRING_4,
	I_STRING_5, I_STRING_6, I_STRING_7, I_STRING_8, I_STRING_9, I_STRING_10, I_STRING_11};
	int	i;

	i = 0;
	while (i < DSCRIP_STR_INV)
	{
		if (!(env->hud.text.i_obj_description[i] = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
			return (0);
		i++;
	}
	return (1);
}

int	set_pick_strings(t_env *env)
{
	const char	*string[14] = {P_STRING_0, P_STRING_1, P_STRING_2, P_STRING_3, P_STRING_4,
	P_STRING_5, P_STRING_6, P_STRING_7, P_STRING_8, P_STRING_9, P_STRING_10, P_STRING_11,
	P_STRING_12, P_STRING_13};
	int	i;

	i = 0;
	while (i < HUD_PICK_OBJ)
	{
		if (!(env->hud.text.pick_objects[i] = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
			return (0);
		i++;
	}
	return (1);
}

int			set_simple_strings(t_env *env, int i, int j)
{
	const char		*string[24] = {STRING_0, STRING_1, STRING_2, STRING_3, STRING_4,
	STRING_5, STRING_6, STRING_7, STRING_8, STRING_9, STRING_10, STRING_11,
	STRING_12, STRING_13, STRING_14, STRING_15,	STRING_16, STRING_17, STRING_18,
	STRING_19, STRING_20, STRING_21, STRING_22, STRING_23};

	while (i < UI_NB_STRING)
	{
		if (i < UI_NB_STRING - UI_NB_STR_INV)
		{
			if (!(env->hud.text.string[i] = ui_create_simple_string((t_font){WHITE,
			string[i], env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
				return (0);
		}
		else
		{
			if (!(env->hud.text.t_inv[j] = ui_create_simple_string((t_font){WHITE,
			string[i], env->hud.text.doom, (t_vtx){0, 0}, 0, -1, -1})))
				return (0);
			j++;
		}
		i++;
	}
	return (set_inv_strings(env)
	&& set_pick_strings(env));
}
