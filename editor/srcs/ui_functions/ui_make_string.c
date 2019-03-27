/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/26 15:48:34 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** if rect.w != 0 && -> srf.w > rect.w -> do not print and return (0)
** else -> print and return (1)
*/

int		ui_make_string(t_rect rect, char *text, t_data *data)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*srf;
	SDL_Color			color;

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	color = ui_hex_to_rgb(rect.color);
	if (!(srf = TTF_RenderText_Blended(data->font, text, color)))
		ui_error_exit_sdl("Libui: Error while making surface", data);
	sdl_rect.w = (sdl_rect.h * srf->w) / srf->h;
	SDL_BlitScaled(srf, 0, data->surface, &sdl_rect);
	SDL_FreeSurface(srf);
	return (!(rect.w > 0 && sdl_rect.w > rect.w));
}
