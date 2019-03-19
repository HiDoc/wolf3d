/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:21:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/19 20:01:23 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Color	ui_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

void		ui_draw_string(SDL_Surface *dst_surface, SDL_Rect rect,
			char *text, Uint32 color, t_env *env)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*surface;
	SDL_Color			sdlcolor;

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	sdlcolor = ui_hex_to_rgb(color);
	if (!(surface = TTF_RenderText_Blended(env->arial_font, text, sdlcolor)))
	{
		ft_putendl(TTF_GetError()); // provisoire
		exit(EXIT_FAILURE); // provisoire : rediriger erreur
	}
	sdl_rect.w = (sdl_rect.h * surface->w) / surface->h;
	SDL_BlitScaled(surface, 0, dst_surface, &sdl_rect);
	SDL_FreeSurface(surface);
}
