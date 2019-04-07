/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/06 13:11:29 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_string(SDL_Rect  rect, char *text, t_data *data)
{
	SDL_Rect			newrect;
	SDL_Surface			*srf;
	SDL_Color			color;

	newrect = rect;
	color = (SDL_Color){255, 255, 255, 255};
	if (!(srf = TTF_RenderText_Blended(data->font, text, color)))
		ui_error_exit_sdl("Libui: Error while making surface", data);
	newrect.w = (newrect.h * srf->w) / srf->h;
	SDL_BlitScaled(srf, 0, data->surface, &newrect);
	SDL_FreeSurface(srf);
}
