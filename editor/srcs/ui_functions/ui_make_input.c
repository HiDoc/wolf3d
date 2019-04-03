/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:02:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/03 17:04:23 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_make_input(SDL_Surface *surface, t_elem *elem, t_data *data)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*srf;
	SDL_Color			color;

	ui_make_rect(surface, elem->rect);
	if (elem->str)
	{
		sdl_rect = (SDL_Rect){
		elem->rect.x, elem->rect.y,
		elem->rect.w, elem->rect.h};
		color = (SDL_Color){255, 255, 255, 255};
		if (!(srf = TTF_RenderText_Blended(data->font, elem->str, color)))
			ui_error_exit_sdl("Libui: Error while making surface", data);
		sdl_rect.w = (sdl_rect.h * srf->w) / srf->h;
		elem->str_max = (sdl_rect.w + sdl_rect.h > elem->rect.w) ? 1 : 0;
		SDL_BlitScaled(srf, 0, data->surface, &sdl_rect);
		SDL_FreeSurface(srf);
	}
}
