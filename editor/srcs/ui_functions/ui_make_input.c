/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:02:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/03 14:30:58 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_make_input(SDL_Surface *surface, t_elem *elem, t_data *data)
{
	SDL_Rect			rect;
	SDL_Surface			*srf;
	SDL_Color			color;

	ui_make_rect(surface, elem->rect, elem->color);
	if (elem->str)
	{
		rect = elem->rect;
		color = (SDL_Color){255, 255, 255, 255};
		if (!(srf = lt_push(
		TTF_RenderText_Blended(data->font, elem->str, color), srf_del)))
			ui_error_exit_sdl("Libui: Error while making surface");
		rect.w = (rect.h * srf->w) / srf->h;
		elem->str_max = (rect.w + rect.h > elem->rect.w) ? 1 : 0;
		if ((SDL_BlitScaled(srf, 0, data->surface, &rect)) < 0)
			ui_error_exit_sdl("Libui: blit error in ui_make_input");
		lt_release(&srf);
	}
}
