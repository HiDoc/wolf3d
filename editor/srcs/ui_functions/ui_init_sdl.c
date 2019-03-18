/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init_sdl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:16:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/15 16:07:38 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_init_sdl(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(&(data->sdl), sizeof(t_sdl));
	ft_bzero(&(data->objects.circle), sizeof(t_round) * 100);
	ft_bzero(&(data->objects.square), sizeof(t_square) * 100);
	data->objects.circle_index = 0;
	data->objects.square_index = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ui_error_exit_sdl("Libui: Unable to initialize SDL2", data);
	if (TTF_Init() < 0)
		ui_error_exit_sdl("Libui: Unable to initialize SDL TTF", data);
}
