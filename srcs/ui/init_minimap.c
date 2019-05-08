/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:03:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 22:04:51 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		get_map_minmax(t_env *env)
{
	const t_engine	*engine = &(env->engine);
	t_minimap		*minimap;
	t_vtx			*vtx;
	unsigned int	i;
	unsigned int	j;

	minimap = &(env->engine.minimap);
	env->engine.minimap.xmin = W;
	env->engine.minimap.xmax = -1;
	env->engine.minimap.ymin = H;
	env->engine.minimap.ymax = -1;
	i = -1;
	while (++i < engine->nsectors)
	{
		j = -1;
		while (++j < engine->sectors[i].npoints)
		{
			vtx = &engine->sectors[i].vertex[j];
			(vtx->x < minimap->xmin) ? minimap->xmin = vtx->x : 0;
			(vtx->x > minimap->xmax) ? minimap->xmax = vtx->x : 0;
			(vtx->y < minimap->ymin) ? minimap->ymin = vtx->y : 0;
			(vtx->y > minimap->ymax) ? minimap->ymax = vtx->y : 0;
		}
	}
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
		while (j < engine->sectors[i].npoints)
		{
			edge = (t_edge){engine->sectors[i].vertex[j],
			engine->sectors[i].vertex[j + 1]};
			edge.v1.x = edge.v1.x * COEF_MINIMAP + MINIMAP_SIZE / 2;
			edge.v1.y = edge.v1.y * COEF_MINIMAP + MINIMAP_SIZE / 2;
			edge.v2.x = edge.v2.x * COEF_MINIMAP + MINIMAP_SIZE / 2;
			edge.v2.y = edge.v2.y * COEF_MINIMAP + MINIMAP_SIZE / 2;
			ui_draw_line(surface, edge, C_CYAN);
			j++;
		}
		i++;
	}
}

static void		draw_background(SDL_Surface *surface)
{
	t_circle		circle;

	circle = (t_circle){MINIMAP_SIZE / 2, MINIMAP_SIZE / 2,
	(MINIMAP_SIZE - 15) / 2, 0x0C0A15E0};
	ui_draw_full_circle(surface, circle);
	circle = (t_circle){MINIMAP_SIZE / 2, MINIMAP_SIZE / 2,
	MINIMAP_SIZE / 2, C_WHITE};
	ui_draw_circle(surface, circle);
}

static void		draw_player(SDL_Surface *surface)
{
	t_circle	circle;
	t_vtx		vtx;

	circle = (t_circle){MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, 5, C_CYAN};
	ui_draw_full_circle(surface, circle);
	vtx = (t_vtx){circle.x, circle.y};
	ui_draw_vector(surface, vtx, 240 * (M_PI / 180), (t_vtx){0, 30});
	ui_draw_vector(surface, vtx, 300 * (M_PI / 180), (t_vtx){0, 30});
}

void			init_minimap(t_env *env)
{
	t_minimap		*minimap;

	minimap = &(env->engine.minimap);
	get_map_minmax(env);
	minimap->origin.x = W - MINIMAP_SIZE - 10;
	minimap->origin.y = 10;
	minimap->surface = make_surface(
	(minimap->xmax - minimap->xmin) * COEF_MINIMAP + MINIMAP_SIZE,
	(minimap->ymax - minimap->ymin) * COEF_MINIMAP + MINIMAP_SIZE);
	minimap->background = make_surface(MINIMAP_SIZE, MINIMAP_SIZE);
	draw_sectors(minimap->surface, &(env->engine));
	draw_background(minimap->background);
	draw_player(minimap->background);
}
