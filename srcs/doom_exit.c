/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:43:01 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/09 00:25:25 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		wdw_del(void **ap)
{
	SDL_Window      *window;

	window = (SDL_Window *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyWindow(window);
		window = 0;
	}
}

void		rdr_del(void **ap)
{
	SDL_Renderer      *renderer;

	renderer = (SDL_Renderer *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyRenderer(renderer);
		renderer = 0;
	}
}

void		srf_del(void **ap)
{
	SDL_Surface		*surface;

	surface = (SDL_Surface *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}
}

void		txr_del(void **ap)
{
	SDL_Texture		*texture;

	texture = (SDL_Texture *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyTexture(texture);
		texture = 0;
	}
}

void		crs_del(void **ap)
{
	SDL_Cursor		*cursor;

	cursor = (SDL_Cursor *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeCursor(cursor);
		cursor = 0;
	}
}

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
