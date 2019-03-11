/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/11 17:32:58 by sgalasso         ###   ########.fr       */
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
		edge = (t_edge){
		engine->sectors[i].vertex[engine->sectors[i].npoints],
		engine->sectors[i].vertex[0]};

		edge = current_edge(engine->player.where, edge.v1, edge.v2);

		edge.v1.x *= COEF_MINIMAP;
		edge.v1.y *= COEF_MINIMAP;
		edge.v2.x *= COEF_MINIMAP;
		edge.v2.y *= COEF_MINIMAP;

		edge = rotation_edge(engine->player, edge);

		edge.v1.x += MINIMAP_W / 2;
		edge.v1.y += MINIMAP_H / 2;
		edge.v2.x += MINIMAP_W / 2;
		edge.v2.y += MINIMAP_H / 2;

		ui_draw_line(surface, edge, C_CYAN);

		while (j < engine->sectors[i].npoints - 1)
		{
			edge = (t_edge){
			(t_vtx){
			engine->sectors[i].vertex[j].x,
			engine->sectors[i].vertex[j].y},
			(t_vtx){
			engine->sectors[i].vertex[j + 1].x,
			engine->sectors[i].vertex[j + 1].y}
			};

			edge = current_edge(engine->player.where, edge.v1, edge.v2);

			edge.v1.x *= COEF_MINIMAP;
			edge.v1.y *= COEF_MINIMAP;
			edge.v2.x *= COEF_MINIMAP;
			edge.v2.y *= COEF_MINIMAP;

			edge = rotation_edge(engine->player, edge);

			edge.v1.x += MINIMAP_W / 2;
			edge.v1.y += MINIMAP_H / 2;
			edge.v2.x += MINIMAP_W / 2;
			edge.v2.y += MINIMAP_H / 2;

			ui_draw_line(surface, edge, C_CYAN);

			j++;
		}
		i++;
	}
}

static void	draw_player(SDL_Surface *surface)
{
	SDL_Rect	rect;
	t_edge		edge;

	// player position
	rect = (SDL_Rect){(MINIMAP_W / 2) - 5, (MINIMAP_H / 2) - 5, 10, 10};
	ui_draw_full_rect(surface, rect, C_BLUE);

	// player direction
	edge = (t_edge){(t_vtx){rect.x + 5, rect.y + 5},
	(t_vtx){rect.x + 5, rect.y - 10}};
	ui_draw_line(surface, edge, C_CYAN);
}

void		ui_minimap(t_env *env)
{
	SDL_Surface		*surface;
	SDL_Rect		rect;

	if (!(surface = ui_make_surface(MINIMAP_H, MINIMAP_W)))
	{
		printf("Doom_nukem: minimap: %s\n", SDL_GetError());
		exit(EXIT_FAILURE); // retourner erreur
	}

	// background
	rect = (SDL_Rect){0, 0, MINIMAP_W, MINIMAP_H};
	ui_draw_rect(surface, rect, C_BLACK);

	// walls
	draw_sectors(surface, &(env->engine));

	// player
	draw_player(surface);


	// recoder BlitSurface
	rect = (SDL_Rect){W - MINIMAP_W - 10, 10, MINIMAP_W, MINIMAP_H};
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
