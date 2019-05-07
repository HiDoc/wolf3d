/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 17:23:22 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_string(SDL_Rect rect, char *text, Uint32 color, t_data *data)
{
	SDL_Rect			newrect;
	SDL_Surface			*srf;
	SDL_Color			sdlcolor;

	newrect = rect;
	sdlcolor = ui_hex_to_rgb(color);
	if (!(srf = lt_push(
			TTF_RenderText_Blended(data->font, text, sdlcolor), srf_del)))
		ui_error_exit_sdl("Libui: Error while making surface");
	newrect.w = (newrect.h * srf->w) / srf->h;
	if ((SDL_BlitScaled(srf, 0, data->surface, &newrect)) < 0)
		ui_error_exit_sdl("Libui: blit error in ui_make_string");
	lt_release((void**)&srf);
}
