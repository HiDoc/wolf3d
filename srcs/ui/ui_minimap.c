/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/11 16:16:26 by sgalasso         ###   ########.fr       */
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
		ui_draw_line(surface, edge, C_CYAN);
		while (j < engine->sectors[i].npoints - 1)
		{
			edge = (t_edge){
			(t_vtx){
			engine->sectors[i].vertex[j].x * COEF_MINIMAP - engine->player.where.x * COEF_MINIMAP + MINIMAP_W / 2,
			engine->sectors[i].vertex[j].y * COEF_MINIMAP - engine->player.where.y * COEF_MINIMAP + MINIMAP_H / 2},
			(t_vtx){
			engine->sectors[i].vertex[j + 1].x * COEF_MINIMAP - engine->player.where.x * COEF_MINIMAP + MINIMAP_W / 2,
			engine->sectors[i].vertex[j + 1].y * COEF_MINIMAP - engine->player.where.y * COEF_MINIMAP + MINIMAP_H / 2}
			};

			ui_draw_line(surface, edge, C_CYAN);

			j++;
		}
		i++;
	}
}

static void	draw_player(SDL_Surface *surface, t_engine *engine)
{
	SDL_Rect	rect;
	t_vtx		vtx;

	// player position
	rect = (SDL_Rect){(MINIMAP_W / 2) - 5, (MINIMAP_H / 2) - 5, 10, 10};
	ui_draw_full_rect(surface, rect, C_BLUE);

	// player direction
	vtx = (t_vtx){rect.x + 5, rect.y + 5};
	ui_draw_vector(surface, vtx, engine->player.angle, 15, C_RED);
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
	draw_player(surface, &(env->engine));


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
