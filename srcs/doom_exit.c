/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:43:01 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 23:53:30 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		doom_release(void)
{
	//lt_destroy();
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

void		doom_error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	doom_release();
	exit(EXIT_FAILURE);
}

void		doom_exit(void)
{
	doom_release();
	//exit(EXIT_SUCCESS);
}
