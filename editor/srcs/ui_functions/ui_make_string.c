/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/04 10:21:41 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_string(t_rect rect, char *text, t_data *data)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*surface;
	SDL_Color			color;

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	color = ui_hex_to_rgb(rect.color);
	if (!(surface = TTF_RenderText_Blended(data->font, text, color)))
		ui_error_exit_sdl("Libui: Error while making surface", data);
	sdl_rect.w = (sdl_rect.h * surface->w) / surface->h;
	SDL_BlitScaled(surface, 0, data->surface, &sdl_rect);
	SDL_FreeSurface(surface);
}
