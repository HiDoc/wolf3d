/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_exit_sdl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/14 17:49:21 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_exit_sdl(t_data *data)
{
	// free images
	// free sector + vertex
	SDL_FreeSurface(data->surface);
	TTF_CloseFont(data->font);
	SDL_DestroyRenderer(data->sdl.renderer);
	SDL_DestroyWindow(data->sdl.window);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
