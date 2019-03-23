/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:35:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/23 11:03:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	tga2sur(t_tga *tga, SDL_Surface *surface, t_win *wn)
{
	SDL_Texture *txt;

	SDL_SetRenderDrawColor(wn->rend,0,0,0,0);
	SDL_RenderClear(wn->rend);
//	surface = set_surface(tga);
	surface = SDL_CreateRGBSurfaceWithFormatFrom(tga->pxl,tga->w, tga->h, 32, 4 * tga->w, SDL_PIXELFORMAT_ARGB32);
	txt = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_RenderCopy(wn->rend, txt, NULL, NULL);
	SDL_RenderPresent(wn->rend);
	SDL_FreeSurface(surface);
}

void		load_texture(char *path, t_win *wn)
{
	SDL_Surface	*surface;
	t_tga		*tga;

	surface = NULL;
	tga = NULL;
	if (!(tga = (t_tga *)malloc(sizeof(t_tga))))
		stop_exec("Cant malloc tga\n", wn);
	tga_load(tga, path);
	tga2sur(tga, surface, wn);
}

void		initload(t_win **wn)
{
	SDL_PollEvent(&(*wn)->ev);
	printf("Debut load\n");
/*	load_texture("./texture/home.tga", *wn);
	SDL_Delay(3000);
	load_texture("./texture/01.tga", *wn);
	SDL_Delay(3000);
	load_texture("./texture/02.tga", *wn);
	SDL_Delay(3000);
	load_texture("./texture/03.tga", *wn);
	SDL_Delay(3000);
*/	load_texture("./texture/icon.tga", *wn);
/*	SDL_Delay(3000);
	load_texture("./texture/ak47.tga", *wn);
	SDL_Delay(3000);
	load_texture("./texture/4.tga", *wn);
	SDL_Delay(3000);
	load_texture("./texture/5.tga", *wn);
	SDL_Delay(3000);
	load_texture("./texture/6.tga", *wn);
	SDL_Delay(3000);
	load_texture("./texture/chelou.tga", *wn);
	SDL_Delay(3000);
*/	printf("Fin load\n");
}
