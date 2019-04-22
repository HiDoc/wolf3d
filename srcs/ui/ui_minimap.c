/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/22 13:10:09 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int      point_in_circle(t_vtx vtx, t_circle circle)
{
	return (sqrt(pow(vtx.x - circle.x, 2) + pow(vtx.y - circle.y, 2))
	< circle.radius);
}

SDL_Surface     *rotate_surface(SDL_Rect src_rect, SDL_Surface *src,
		SDL_Surface *dst, t_vtx origin, t_env *env)
{
	const t_player  plr = env->engine.player;
	const t_vtx     c = {src_rect.w / 2, src_rect.h / 2};
	t_vtx           dest;
	float           y;
	float           x;
	Uint32          color;
	const float     angle = -plr.angle;
	t_vtx			vtx;
	t_circle		circle;

	circle = (t_circle){
	(MINIMAP_SIZE) / 2 + origin.x,
	(MINIMAP_SIZE) / 2 + origin.y,
	(MINIMAP_SIZE - 15) / 2, 0x0C0A15E0};

	y = 0;
	while (y < src_rect.h)
	{
		x = 0;
		while (x < src_rect.w)
		{
			vtx = (t_vtx){origin.x + x, origin.y + y};
			if (point_in_circle(vtx, circle))
			{
				dest = (t_vtx){
				c.x + (x - c.x) * sin(angle) - (y - c.y) * cos(angle),
				c.y + (x - c.x) * cos(angle) + (y - c.y) * sin(angle)};
				if ((color = getpixel(src, src_rect.x + dest.x,
						src_rect.y + dest.y)))
					setpixel(dst, origin.x + x, origin.y + y, color);
			}
			x++;
		}
		y++;
	}
	return (dst);
}

static t_edge		translate_edge(t_vctr player_position, t_vtx v1, t_vtx v2)
{
	t_edge      edge;

	edge.v1 = (t_vtx){v1.x - player_position.x, v1.y - player_position.y};
	edge.v2 = (t_vtx){v2.x - player_position.x, v2.y - player_position.y};
	return (edge);
}

static t_edge		rotate_edge(t_player player, t_edge v)
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

static void			draw_objects(SDL_Surface *surface, t_engine *engine)
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
			edge = translate_edge(engine->player.where, obj->vertex, obj->vertex);

			// rotation
			edge = rotate_edge(engine->player, edge);

			// scale
			rect = (SDL_Rect){
				edge.v1.x * COEF_MINIMAP, edge.v1.y * COEF_MINIMAP,
					10, 10};

			// origin
			rect = (SDL_Rect){
				rect.x + engine->minimap.origin.x + MINIMAP_SIZE / 2 - 5,
					rect.y + engine->minimap.origin.y + MINIMAP_SIZE / 2 - 5,
					10, 10};

			ui_draw_rect(surface, rect, C_GREEN);
			obj = obj->next;
		}
		i++;
	}
}

static void			draw_entities(SDL_Surface *surface, t_engine *engine)
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
			enmy_where = (t_vtx){enemy->player.where.x, enemy->player.where.x};
			// translation
			edge = translate_edge(engine->player.where,
					enmy_where, enmy_where);

			// rotation
			edge = rotate_edge(engine->player, edge);

			// scale
			rect = (SDL_Rect){
				edge.v1.x * COEF_MINIMAP, edge.v1.y * COEF_MINIMAP,
					10, 10};

			// origin
			rect = (SDL_Rect){
				rect.x + engine->minimap.origin.x + MINIMAP_SIZE / 2 - 5,
					rect.y + engine->minimap.origin.y + MINIMAP_SIZE / 2 - 5,
					10, 10};

			ui_draw_rect(surface, rect, C_RED);
			enemy = enemy->next;
		}
		i++;
	}
}

static void			draw_compass(SDL_Surface *surface, t_env *env)
{
	SDL_Rect    rect;
	t_vtx       vtx;
	float       start;
	float       size;
	int         i;

	i = 0;
	while (i < 16)
	{
		vtx = (t_vtx){
			env->engine.minimap.origin.x + MINIMAP_SIZE / 2,
				env->engine.minimap.origin.y + MINIMAP_SIZE / 2};

		start = MINIMAP_SIZE / 2 - 15;
		size = MINIMAP_SIZE / 2 - 7;

		rect = (SDL_Rect){
		vtx.x + cos(i * (M_PI / 8) - env->engine.player.angle) * size - 8,
		vtx.y + sin(i * (M_PI / 8) -  env->engine.player.angle) * size - 15,
				0, 30};

		if (i == 0)
			ui_draw_string(surface, rect, "N", 0xFFFFFFFF, env);
		if (i != 0)
		{
			ui_draw_vector(surface, vtx,
			i * (M_PI / 8)  - env->engine.player.angle, start, size, C_WHITE);
		}
		i++;
	}
}

void		ui_minimap(t_env *env)
{
	const t_minimap		*minimap = &(env->engine.minimap);

	SDL_Rect src_rect = (SDL_Rect){
		(env->engine.player.where.x * COEF_MINIMAP),
			(env->engine.player.where.y * COEF_MINIMAP),
			MINIMAP_SIZE, MINIMAP_SIZE};

	if ((SDL_BlitScaled(minimap->background, 0, env->sdl.surface,
			&((SDL_Rect){minimap->origin.x, minimap->origin.y,
			MINIMAP_SIZE, MINIMAP_SIZE}))) < 0)
		doom_error_exit("Doom_nukem: Blit error on ui_minimap");

	env->sdl.surface = rotate_surface(src_rect,
	minimap->surface, env->sdl.surface, minimap->origin, env);

	draw_objects(env->sdl.surface, &(env->engine));
	draw_entities(env->sdl.surface, &(env->engine));
	draw_compass(env->sdl.surface, env);
}
