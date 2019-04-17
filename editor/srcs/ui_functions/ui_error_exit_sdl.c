/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:00:02 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 22:04:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_error_exit_sdl(char *msg)
{
	ft_putendl_fd(msg, 2);
	lt_destroy();
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
