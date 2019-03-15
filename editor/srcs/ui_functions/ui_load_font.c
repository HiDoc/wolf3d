/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_load_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:15:54 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/02 17:49:06 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_load_font(char *path, t_data *data)
{
	if (!(data->font = TTF_OpenFont(path, 100)))
		ui_error_exit_sdl("Libui: SDL_TTF bad font path", data);
}
