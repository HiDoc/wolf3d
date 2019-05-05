/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init_sdl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:16:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/05 17:14:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_init_sdl(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(&(data->sdl), sizeof(t_sdl));
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		ui_error_exit_sdl("Libui: Unable to initialize SDL2");
	if (TTF_Init() < 0)
		ui_error_exit_sdl("Libui: Unable to initialize SDL TTF");
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
		ui_error_exit_sdl("Editor error, can't Mix_OpenAudio");
}
