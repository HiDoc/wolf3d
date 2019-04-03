/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:03:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/29 18:27:00 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		draw_player(SDL_Surface *surface)
{
	t_circle	circle;

	// player position
	circle = (t_circle){MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, 5, C_CYAN};
	ui_draw_full_circle(surface, circle);

	// player fov
	ui_draw_vector(surface, (t_vtx){circle.x, circle.y},
	240 * M_PI / 180, 0, 30, 0xFBFCAEFF);
	ui_draw_vector(surface, (t_vtx){circle.x, circle.y},
	300 * M_PI / 180, 0, 30, 0xFBFCAEFF);
}

static void		get_map_minmax(t_env *env)
{
	t_minimap		*minimap = &(env->engine.minimap);
	const t_engine	*engine = &(env->engine);
	unsigned int	i;
	unsigned int	j;

	env->engine.minimap.xmin = W;
	env->engine.minimap.xmax = -1;
	env->engine.minimap.ymin = H;
	env->engine.minimap. ymax = -1;

	i = 0;
	while (i < engine->nsectors)
	{
		j = 0;
		while (j < engine->sectors[i].npoints)
		{
			if (engine->sectors[i].vertex[j].x < minimap->xmin)
				minimap->xmin = engine->sectors[i].vertex[j].x;
			else if (engine->sectors[i].vertex[j].x > minimap->xmax)
				minimap->xmax = engine->sectors[i].vertex[j].x;
			if (engine->sectors[i].vertex[j].y < minimap->ymin)
				minimap->ymin = engine->sectors[i].vertex[j].y;
			else if (engine->sectors[i].vertex[j].y > minimap->ymax)
				minimap->ymax = engine->sectors[i].vertex[j].y;
			j++;
		}
		i++;
	}
}

static void     draw_sectors(SDL_Surface *surface, t_engine *engine)
{
	t_edge          edge;
	unsigned int    i;
	unsigned int    j;

	i = 0;
	while (i < engine->nsectors)
	{
		j = 0;
		while (j < engine->sectors[i].npoints)
		{
			edge = (t_edge){
				engine->sectors[i].vertex[j],
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

void	draw_background(SDL_Surface *surface)
{
	t_circle            circle;
	SDL_Rect            rect;

	rect = (SDL_Rect){0, 0, MINIMAP_SIZE, MINIMAP_SIZE}; // to remove
	ui_draw_rect(surface, rect, C_RED); // to remove

	circle = (t_circle){MINIMAP_SIZE / 2, MINIMAP_SIZE / 2,
	MINIMAP_SIZE / 2, 0x0C0A15FF};

	ui_draw_full_circle(surface, circle);

	circle = (t_circle){MINIMAP_SIZE / 2, MINIMAP_SIZE / 2,
	MINIMAP_SIZE / 2, C_WHITE};

	ui_draw_circle(surface, circle);
}

int			init_minimap(t_env *env)
{
	t_minimap		*minimap = &(env->engine.minimap);

	get_map_minmax(env);

	minimap->origin.x = W - MINIMAP_SIZE - 10;
	minimap->origin.y = 10;

	if (!(minimap->surface = ui_make_surface(
	(minimap->xmax - minimap->xmin) * COEF_MINIMAP + MINIMAP_SIZE,
	(minimap->ymax - minimap->ymin) * COEF_MINIMAP + MINIMAP_SIZE)))
		return (0);
	draw_sectors(minimap->surface, &(env->engine)); // a proteger ?

	if (!(minimap->background = ui_make_surface(
	MINIMAP_SIZE, MINIMAP_SIZE)))
		return (0);
	draw_background(minimap->background);
	draw_player(minimap->background);

	return (1);
}
