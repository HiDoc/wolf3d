/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/13 15:49:29 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*static */t_edge	rotate_edge(t_player player, t_edge v)
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

/*static */void		draw_sectors(SDL_Surface *surface, t_engine *engine)
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

		//edge = translate_edge(engine->player.where, edge.v1, edge.v2);

		edge.v1.x *= COEF_MINIMAP;
		edge.v1.y *= COEF_MINIMAP;
		edge.v2.x *= COEF_MINIMAP;
		edge.v2.y *= COEF_MINIMAP;

		/*edge = rotate_edge(engine->player, edge);

		edge.v1.x += MINIMAP_SIZE / 2 % MINIMAP_SIZE;
		edge.v1.y += MINIMAP_SIZE / 2 % MINIMAP_SIZE;
		edge.v2.x += MINIMAP_SIZE / 2 % MINIMAP_SIZE;
		edge.v2.y += MINIMAP_SIZE / 2 % MINIMAP_SIZE;*/

		ui_draw_line(surface, edge, C_CYAN);

		while (j < engine->sectors[i].npoints - 1)
		{
			edge = (t_edge){
			engine->sectors[i].vertex[j],
			engine->sectors[i].vertex[j + 1]};

			//edge = translate_edge(engine->player.where, edge.v1, edge.v2);

			edge.v1.x *= COEF_MINIMAP;
			edge.v1.y *= COEF_MINIMAP;
			edge.v2.x *= COEF_MINIMAP;
			edge.v2.y *= COEF_MINIMAP;

			/*edge = rotate_edge(engine->player, edge);

			edge.v1.x += MINIMAP_SIZE / 2 % MINIMAP_SIZE;
			edge.v1.y += MINIMAP_SIZE / 2 % MINIMAP_SIZE;
			edge.v2.x += MINIMAP_SIZE / 2 % MINIMAP_SIZE;
			edge.v2.y += MINIMAP_SIZE / 2 % MINIMAP_SIZE;*/

			ui_draw_line(surface, edge, C_CYAN);

			j++;
		}
		i++;
	}
}

/*static */void		draw_player(SDL_Surface *surface)
{
	SDL_Rect	rect;
	t_edge		edge;

	// player position
	rect = (SDL_Rect){(MINIMAP_SIZE / 2) - 5, (MINIMAP_SIZE / 2) - 5, 10, 10};
	ui_draw_full_rect(surface, rect, C_BLUE);

	// player direction
	edge = (t_edge){(t_vtx){rect.x + 5, rect.y + 5},
		(t_vtx){rect.x + 5, rect.y - 10}};
	ui_draw_line(surface, edge, C_CYAN);
}

void		ui_minimap(t_env *env)
{
	//SDL_Surface		*surface;
	//SDL_Rect		srcrect;
	//SDL_Rect		dstrect;
	t_circle		circle;

	// Fonction provisoire XMaxMin
	const t_engine	*engine = &env->engine;
	int				xmin = W;
	int				xmax = -1;
	int				ymin = H;
	int				ymax = -1;
	unsigned int	i;
	unsigned int	j;
	i = 0;
	while (i < engine->nsectors)
	{
		j = 0;
		while (j < engine->sectors[i].npoints)
		{
			if (engine->sectors[i].vertex[j].x < xmin)
				xmin = engine->sectors[i].vertex[j].x;
			else if (engine->sectors[i].vertex[j].x > xmax)
				xmax = engine->sectors[i].vertex[j].x;
			if (engine->sectors[i].vertex[j].y < ymin)
				ymin = engine->sectors[i].vertex[j].y;
			else if (engine->sectors[i].vertex[j].y > ymax)
				ymax = engine->sectors[i].vertex[j].y;
			j++;
		}
		i++;
	}
	//////////////////////////////
	

	/*if (!(surface = ui_make_surface(ymax + 1, xmax + 1)))
	{
		printf("Doom_nukem: minimap: %s\n", SDL_GetError());
		exit(EXIT_FAILURE); // retourner erreur
	}*/

	// drawing sectors on area
	draw_sectors(env->sdl.surface, &(env->engine));

	// background
	circle = (t_circle){
	W - MINIMAP_SIZE / 2 - 10, MINIMAP_SIZE / 2 + 10,
	MINIMAP_SIZE / 4, 0x0C0A15FF};
	ui_draw_full_circle(env->sdl.surface, circle);
	circle = (t_circle){
	W - MINIMAP_SIZE / 2 - 10, MINIMAP_SIZE / 2 + 10,
	MINIMAP_SIZE / 2, C_WHITE};
	ui_draw_circle(env->sdl.surface, circle);

	/*// player
	draw_player(surface);
*/
	// recoder BlitSurface
	/*srcrect = (SDL_Rect){
	env->engine.player.where.x, env->engine.player.where.y,
	xmax, xmax}; // set relatif
	dstrect = (SDL_Rect){W - MINIMAP_SIZE - 10, 10, MINIMAP_SIZE, MINIMAP_SIZE};
	SDL_UnlockSurface(env->sdl.surface);
	if ((SDL_BlitScaled(surface, &srcrect, env->sdl.surface, &dstrect)) < 0)
	{
		printf("Doom_nukem: minimap: %s\n", SDL_GetError());
		exit(EXIT_FAILURE); // retourner erreur
	}
	SDL_LockSurface(env->sdl.surface);*/
	/////////////////////

	//SDL_FreeSurface(surface);
}
