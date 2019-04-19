/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:26:54 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 22:49:42 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			ui_make_window(char *name, t_data *data)
{
	if (!(data->sdl.window = lt_push(SDL_CreateWindow(name,
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0), wdw_del)))
		ui_error_exit_sdl("Libui: Unable to make window");
	SDL_RaiseWindow(data->sdl.window);
	if (!(data->sdl.renderer = lt_push(SDL_CreateRenderer(data->sdl.window, -1,
	SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_SOFTWARE), rdr_del)))
		ui_error_exit_sdl("Libui: Unable to make renderer");
	if (!(data->surface = lt_push(ui_make_surface(WIN_H, WIN_W), srf_del)))
		ui_error_exit_sdl("Libui: Unable to make surface");
}
