/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/20 14:50:48 by sgalasso         ###   ########.fr       */
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

static void		draw_sectors(SDL_Surface *surface,
				t_minimap *minimap, t_engine *engine)
{
	t_edge			edge;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < engine->nsectors)
	{
		j = 0;
		while (j < engine->sectors[i].npoints)
		{
			edge = (t_edge){
				engine->sectors[i].vertex[j],
				engine->sectors[i].vertex[j + 1]};

			edge = translate_edge(engine->player.where, edge.v1, edge.v2);

			edge = rotate_edge(engine->player, edge);

			edge.v1.x = edge.v1.x * COEF_MINIMAP + minimap->origin.x
				+ MINIMAP_SIZE / 2;
			edge.v1.y = edge.v1.y * COEF_MINIMAP + minimap->origin.y
				+ MINIMAP_SIZE / 2;
			edge.v2.x = edge.v2.x * COEF_MINIMAP + minimap->origin.x
				+ MINIMAP_SIZE / 2;
			edge.v2.y = edge.v2.y * COEF_MINIMAP + minimap->origin.y
				+ MINIMAP_SIZE / 2;

			if (edge.v1.x >= 0 && edge.v1.y >= 0 && edge.v2.x < W && edge.v2.y < H
			&& edge.v1.x < W && edge.v1.y < H && edge.v2.x >= 0 && edge.v2.y >= 0)
				ui_draw_line(surface, edge, C_CYAN);

			j++;
		}
		i++;
	}
}

static void		draw_objects(SDL_Surface *surface, t_minimap *minimap,
				t_engine *engine)
{
	t_wrap_sect		*obj;
	SDL_Rect		rect;
	t_edge			edge;
	unsigned int	i;

	i = 0;
	while (i < engine->nsectors)
	{
		obj = engine->sectors[i].head_object;
		while (obj)
		{
			// translation
			edge = translate_edge(engine->player.where,
					obj->vertex, obj->vertex);

			// rotation
			edge = rotate_edge(engine->player, edge);

			// scale
			rect = (SDL_Rect){
			edge.v1.x * COEF_MINIMAP, 
			edge.v1.y * COEF_MINIMAP,
			10, 10};

			// origin
			rect = (SDL_Rect){
			rect.x + minimap->origin.x + MINIMAP_SIZE / 2 - 5,
			rect.y + minimap->origin.y + MINIMAP_SIZE / 2 - 5,
			10, 10};

			ui_draw_rect(surface, rect, C_GREEN);
			obj = obj->next;
		}
		i++;
	}
}

static void		draw_player(SDL_Surface *surface, t_minimap *minimap)
{
	SDL_Rect	rect;
	t_edge		edge;

	// player position
	//rect = (SDL_Rect){minimap->player.x - 5, minimap->player.y + 5, 10, 10};
	rect = (SDL_Rect){
	minimap->origin.x + MINIMAP_SIZE / 2 - 5,
	minimap->origin.y + MINIMAP_SIZE / 2 - 5, 10, 10};
	ui_draw_full_rect(surface, rect, C_BLUE);

	// player direction
	edge = (t_edge){(t_vtx){rect.x + 5, rect.y + 5},
	(t_vtx){rect.x + 5, rect.y - 10}};
	ui_draw_line(surface, edge, C_CYAN);
}

static void     draw_compass(SDL_Surface *surface, t_minimap *minimap, t_env *env)
{
	SDL_Rect	rect;
	t_vtx		vtx;
	float		start;
	float		size;
	int			i;

	i = 0;
	while (i < 16)
	{
		vtx = (t_vtx){
		minimap->origin.x + MINIMAP_SIZE / 2,
		minimap->origin.y + MINIMAP_SIZE / 2};

		start = MINIMAP_SIZE / 2 - 10;
		size = MINIMAP_SIZE / 2;

		rect.x = vtx.x + cos(i * (M_PI / 8) - env->engine.player.angle)
		* size - 8;
		rect.y = vtx.y + sin(i * (M_PI / 8) -  env->engine.player.angle)
		* size - 15;
		rect.w = 0;
		rect.h = 30;


		if (i == 0)
			ui_draw_string(surface, rect, "N", 0xFFFFFFFF, env);
		else if (i == 4)
			ui_draw_string(surface, rect, "E", 0xFFFFFFFF, env);
		else if (i == 8)
			ui_draw_string(surface, rect, "S", 0xFFFFFFFF, env);
		else if (i == 12)
			ui_draw_string(surface, rect, "O", 0xFFFFFFFF, env);

		if (i % 4 != 0)
		{
			ui_draw_vector(surface, vtx,
			i * (M_PI / 8)  - env->engine.player.angle,
			start, size, C_WHITE);
		}

		i++;
	}
}

void		ui_minimap(t_env *env)
{
	t_minimap		minimap;
	//SDL_Surface		*surface;
	//SDL_Rect		srcrect;
	//SDL_Rect		dstrect;
	t_circle		circle;

	// precalculate
	minimap.origin.x = W - MINIMAP_SIZE - 10;
	minimap.origin.y = 10;
	minimap.player.x = env->engine.player.where.x * COEF_MINIMAP;
	minimap.player.y = env->engine.player.where.y * COEF_MINIMAP;

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

	// background
	SDL_Rect rect = (SDL_Rect){minimap.origin.x, minimap.origin.y, // to remove
	MINIMAP_SIZE, MINIMAP_SIZE}; // to remove
	ui_draw_rect(env->sdl.surface, rect, C_RED); // to remove
	circle = (t_circle){
	minimap.origin.x + MINIMAP_SIZE / 2, minimap.origin.y + MINIMAP_SIZE / 2,
	MINIMAP_SIZE / 2, 0x0C0A15FF};
	ui_draw_full_circle(env->sdl.surface, circle);
	circle = (t_circle){
	minimap.origin.x + MINIMAP_SIZE / 2, minimap.origin.y + MINIMAP_SIZE / 2,
	MINIMAP_SIZE / 2, C_WHITE};
	ui_draw_circle(env->sdl.surface, circle);

	// draw sectors on area
	draw_sectors(env->sdl.surface, &minimap, &(env->engine));

	// draw objects && bots
	draw_objects(env->sdl.surface, &minimap, &(env->engine));
	// draw_bots();

	// draw player
	draw_player(env->sdl.surface, &minimap);

	// draw compass
	draw_compass(env->sdl.surface, &minimap, env);

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
