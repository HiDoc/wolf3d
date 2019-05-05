/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:00:02 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/05 16:51:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_error_exit_sdl(char *msg)
{
	ft_putendl_fd(msg, 2);
	lt_destroy();
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
