/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init_sdl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:16:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 22:07:11 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_init_sdl(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(&(data->sdl), sizeof(t_sdl));
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ui_error_exit_sdl("Libui: Unable to initialize SDL2");
	if (TTF_Init() < 0)
		ui_error_exit_sdl("Libui: Unable to initialize SDL TTF");
}
