/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:18:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 22:27:35 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		dir_del(void **ap)
{
	DIR			*dr;

	dr = (DIR *)(*ap);
	if (ap && *ap)
	{
		closedir(dr);
		dr = 0;
	}
}

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

void		ttf_del(void **ap)
{
	TTF_Font		*font;

	font = (TTF_Font *)(*ap);
	if (ap && *ap)
	{
		TTF_CloseFont(font);
		font = 0;
	}
}
