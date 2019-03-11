/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/11 13:33:33 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_sectors(SDL_Surface *surface, t_engine *engine)
{
	t_edge			edge;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < engine->nsectors)
	{
		j = 0;
		edge = (t_edge){engine->sectors[i].vertex[engine->sectors[i].npoints],
		engine->sectors[i].vertex[0]};
		ui_draw_line(surface, edge, 0x91F1F7FF);
		while (j < engine->sectors[i].npoints - 1)
		{
			edge = (t_edge){
			(t_vtx){
			engine->sectors[i].vertex[j].x * 5,
			engine->sectors[i].vertex[j].y * 5},
			(t_vtx){
			engine->sectors[i].vertex[j + 1].x * 5,
			engine->sectors[i].vertex[j + 1].y * 5}
			};

			ui_draw_line(surface, edge, 0x91F1F7FF);

			j++;
		}
		i++;
	}
}

void		ui_minimap(t_env *env)
{
	int				minimap_w;
	int				minimap_h;

	minimap_w = 350; // set relatif
	minimap_h = 250; // set relatif

	SDL_Surface		*surface;
	SDL_Rect		rect;

	if (!(surface = ui_make_surface(minimap_h, minimap_w)))
	{
		printf("Doom_nukem: minimap: %s\n", SDL_GetError());
		exit(EXIT_FAILURE); // retourner erreur
	}

	rect = (SDL_Rect){0, 0, minimap_w, minimap_h};
	ui_draw_rect(surface, rect, 0x000000FF);


	draw_sectors(surface, &(env->engine));


	// recoder BlitSurface
	rect = (SDL_Rect){W - minimap_w - 10, 10, minimap_w, minimap_h};
	SDL_UnlockSurface(env->sdl.surface);
	if ((SDL_BlitScaled(surface, 0, env->sdl.surface, &rect)) < 0)
	{
		printf("Doom_nukem: minimap: %s\n", SDL_GetError());
		exit(EXIT_FAILURE); // retourner erreur
	}
	SDL_LockSurface(env->sdl.surface);
	/////////////////////

	SDL_FreeSurface(surface);
}
