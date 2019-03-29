/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:30 by abaille           #+#    #+#             */
/*   Updated: 2019/03/28 16:59:33 by fmadura          ###   ########.fr       */
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

int			set_simple_strings(t_env *env, int i, int j)
{
	const char		*string[23] = {STRING_0, STRING_1, STRING_2, STRING_3, STRING_4,
	STRING_5, STRING_6, STRING_7, STRING_8, STRING_9, STRING_10, STRING_11,
	STRING_12, STRING_13, STRING_14, STRING_15,	STRING_16, STRING_17, STRING_18,
	STRING_19, STRING_20, STRING_21, STRING_22};

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
	printf("time font: %u\n", SDL_GetTicks());
	return (1);
}