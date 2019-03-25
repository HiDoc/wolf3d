/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 18:42:55 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_string(t_rect rect, char *text, t_data *data)
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
}
