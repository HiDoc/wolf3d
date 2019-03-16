/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:00:02 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/16 14:23:06 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_error_exit_sdl(char *msg, t_data *data)
{
	// free maps files
	// free images background
	// free images cursor
	// free sector + vertex
	if (data->surface)
		SDL_FreeSurface(data->surface);
	if (data->font)
		TTF_CloseFont(data->font);
	if (data->sdl.renderer)
		SDL_DestroyRenderer(data->sdl.renderer);
	if (data->sdl.window)
		SDL_DestroyWindow(data->sdl.window);
	TTF_Quit();
	SDL_Quit();
	ft_putendl_fd(msg, 2);
	exit(EXIT_SUCCESS);
}
