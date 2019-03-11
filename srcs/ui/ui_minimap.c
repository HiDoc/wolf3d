/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/11 19:53:43 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_edge	translate_edge(t_vctr player_position, t_vtx v1, t_vtx v2)
{
	t_edge      edge;

	edge.v1 = (t_vtx){v1.x - player_position.x, v1.y - player_position.y};
	edge.v2 = (t_vtx){v2.x - player_position.x, v2.y - player_position.y};
	return (edge);
}

static t_edge	rotate_edge(t_player player, t_edge v)
{
	const float pcos = -player.anglecos;
	const float psin = -player.anglesin;
	t_edge      edge;

	edge.v1 = (t_vtx){
	v.v1.x * psin - v.v1.y * pcos,
	v.v1.x * pcos + v.v1.y * psin};

	edge.v2 = (t_vtx){
	v.v2.x * psin - v.v2.y * pcos,
	v.v2.x * pcos + v.v2.y * psin};

	return (edge);
}

static void		draw_sectors(SDL_Surface *surface, t_engine *engine)
{
	t_edge			edge;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < engine->nsectors)
	{
		j = 0;
		edge = (t_edge){
		engine->sectors[i].vertex[engine->sectors[i].npoints - 1],
		engine->sectors[i].vertex[0]};

		edge = translate_edge(engine->player.where, edge.v1, edge.v2);

		edge.v1.x *= COEF_MINIMAP;
		edge.v1.y *= COEF_MINIMAP;
		edge.v2.x *= COEF_MINIMAP;
		edge.v2.y *= COEF_MINIMAP;

		edge = rotate_edge(engine->player, edge);

		edge.v1.x += MINIMAP_W / 2 % MINIMAP_W;
		edge.v1.y += MINIMAP_H / 2 % MINIMAP_H;
		edge.v2.x += MINIMAP_W / 2 % MINIMAP_W;
		edge.v2.y += MINIMAP_H / 2 % MINIMAP_H;

		ui_draw_line(surface, edge, C_CYAN);

		while (j < engine->sectors[i].npoints - 1)
		{
			edge = (t_edge){engine->sectors[i].vertex[j],
				engine->sectors[i].vertex[j + 1]};

			edge = translate_edge(engine->player.where, edge.v1, edge.v2);

			edge.v1.x *= COEF_MINIMAP;
			edge.v1.y *= COEF_MINIMAP;
			edge.v2.x *= COEF_MINIMAP;
			edge.v2.y *= COEF_MINIMAP;

			edge = rotate_edge(engine->player, edge);

			edge.v1.x += MINIMAP_W / 2 % MINIMAP_W;
			edge.v1.y += MINIMAP_H / 2 % MINIMAP_H;
			edge.v2.x += MINIMAP_W / 2 % MINIMAP_W;
			edge.v2.y += MINIMAP_H / 2 % MINIMAP_H;

			ui_draw_line(surface, edge, C_CYAN);

			j++;
		}
		i++;
	}
}

static void		draw_player(SDL_Surface *surface)
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
	t_circle		circle;

	if (!(surface = ui_make_surface(MINIMAP_H, MINIMAP_W)))
	{
		printf("Doom_nukem: minimap: %s\n", SDL_GetError());
		exit(EXIT_FAILURE); // retourner erreur
	}

	// background
	circle = (t_circle){
	MINIMAP_W / 2, MINIMAP_W / 2, MINIMAP_W / 2 - 1, 0x0C0A15FF};
	ui_draw_full_circle(surface, circle);
	circle = (t_circle){
	MINIMAP_W / 2, MINIMAP_W / 2, MINIMAP_W / 2, C_WHITE};
	ui_draw_circle(surface, circle);

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
