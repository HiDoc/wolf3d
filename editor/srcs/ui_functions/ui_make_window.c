/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:26:54 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 16:18:22 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			ui_make_window(char *name, t_data *data)
{
	if (!(data->sdl.window = SDL_CreateWindow(name,
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0)))
		ui_error_exit_sdl("Libui: Unable to make window", data);
	SDL_RaiseWindow(data->sdl.window);
	if (!(data->sdl.renderer = SDL_CreateRenderer(data->sdl.window, -1,
	SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_SOFTWARE)))
		ui_error_exit_sdl("Libui: Unable to make renderer", data);
	if (!(data->surface = ui_make_surface(WIN_H, WIN_W)))
		ui_error_exit_sdl("Libui: Unable to make surface", data);
}
