/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:52:30 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/21 17:46:38 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface		*make_string(t_font str_data)
{
	SDL_Surface		*tmp;
	SDL_Surface		*surface;
	SDL_Color		bg = {42, 42, 42, 42};

	if (!(tmp = lt_push(TTF_RenderText_Shaded(
			str_data.font, str_data.str, str_data.color, bg), srf_del)))
		doom_error_exit("Doom_nukem error on TTF_RenderText_Shaded");
	if (!(surface = lt_push(
			SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB32, 0), srf_del)))
		doom_error_exit("Doom_nukem error on TTF_RenderText_Shaded");
	lt_release(tmp);
	return (surface);
}
