/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 22:07:10 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void			draw_objects(SDL_Surface *surface, t_engine *engine,
					t_circle circle)
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
			edge = translate_edge(engine->player.where, obj->vertex, obj->vertex);
			edge = rotate_edge(engine->player, edge);
			rect = (SDL_Rect){
				edge.v1.x * COEF_MINIMAP, edge.v1.y * COEF_MINIMAP,10, 10};
			rect = (SDL_Rect){
				rect.x + engine->minimap.origin.x + MINIMAP_SIZE / 2 - 5,
				rect.y + engine->minimap.origin.y + MINIMAP_SIZE / 2 - 5,10, 10};
			if (point_in_circle((t_vtx){rect.x, rect.y}, circle))
				ui_draw_rect(surface, rect, C_GREEN);
			obj = obj->next;
		}
		i++;
	}
}

static void			draw_entities(SDL_Surface *surface, t_engine *engine,
					t_circle circle)
{
	t_wrap_enmy		*enemy;
	SDL_Rect		rect;
	t_edge			edge;
	unsigned int	i;
	t_vtx			enmy_where;

	i = 0;
	while (i < engine->nsectors)
	{
		enemy = engine->sectors[i].head_enemy;
		while (enemy)
		{
			enmy_where = (t_vtx){enemy->player.where.x, enemy->player.where.y};
			edge = translate_edge(engine->player.where, enmy_where, enmy_where);
			edge = rotate_edge(engine->player, edge);
			rect = (SDL_Rect){
				edge.v1.x * COEF_MINIMAP, edge.v1.y * COEF_MINIMAP, 10, 10};
			rect = (SDL_Rect){
				rect.x + engine->minimap.origin.x + MINIMAP_SIZE / 2 - 5,
				rect.y + engine->minimap.origin.y + MINIMAP_SIZE / 2 - 5, 10, 10};
			if (point_in_circle((t_vtx){rect.x, rect.y}, circle))
				ui_draw_rect(surface, rect, C_RED);
			enemy = enemy->next;
		}
		i++;
	}
}

static void			draw_compass(SDL_Surface *surface, t_env *env)
{
	const t_player		*player = &env->engine.player;
	const t_minimap		*minimap = &env->engine.minimap;
	t_vtx       		vtx;
	int         		i;

	i = 0;
	while (i < 16)
	{
		vtx.x = minimap->origin.x + MINIMAP_SIZE / 2;
		vtx.y = minimap->origin.y + MINIMAP_SIZE / 2;
		ui_draw_vector(surface, vtx, i * (M_PI / 8) - player->angle,
		(t_vtx){MINIMAP_SIZE / 2 - 15, MINIMAP_SIZE / 2 - 7});
		i++;
	}
}

void		ui_minimap(t_env *env)
{
	const t_minimap		*minimap = &(env->engine.minimap);
	t_circle		circle;

	circle = (t_circle){
	(MINIMAP_SIZE) / 2 + minimap->origin.x, (MINIMAP_SIZE) / 2 + minimap->origin.y,
	(MINIMAP_SIZE - 15) / 2, 0x0C0A15E0};
	SDL_Rect src_rect = (SDL_Rect){
		(env->engine.player.where.x * COEF_MINIMAP),
		(env->engine.player.where.y * COEF_MINIMAP),
		MINIMAP_SIZE, MINIMAP_SIZE};
	if ((SDL_BlitScaled(minimap->background, 0, env->sdl.surface,
		&((SDL_Rect){minimap->origin.x, minimap->origin.y,
		MINIMAP_SIZE, MINIMAP_SIZE}))) < 0)
			doom_error_exit("Doom_nukem: Blit error on ui_minimap");
	env->sdl.surface = rotate_surface(src_rect,
	minimap->surface, env->sdl.surface, minimap->origin, circle, env);
	draw_objects(env->sdl.surface, &(env->engine), circle);
	draw_entities(env->sdl.surface, &(env->engine), circle);
	draw_compass(env->sdl.surface, env);
}
