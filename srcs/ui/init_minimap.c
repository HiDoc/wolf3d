/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:03:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/24 20:50:35 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*static*/ void		draw_player(SDL_Surface *surface)
{
	SDL_Rect	rect;
	t_edge		edge;

	// player position
	//rect = (SDL_Rect){minimap->player.x - 5, minimap->player.y + 5, 10, 10};
	rect = (SDL_Rect){MINIMAP_SIZE / 2 - 5, MINIMAP_SIZE / 2 - 5, 10, 10};
	ui_draw_full_rect(surface, rect, C_BLUE);

	// player direction
	edge = (t_edge){(t_vtx){rect.x + 5, rect.y + 5},
	(t_vtx){rect.x + 5, rect.y - 10}};
	ui_draw_line(surface, edge, C_CYAN);
}

/*static*/ void     draw_compass(SDL_Surface *surface, t_env *env)
{
	SDL_Rect	rect;
	t_vtx		vtx;
	float		start;
	float		size;
	int			i;

	i = 0;
	while (i < 16)
	{
		vtx = (t_vtx){MINIMAP_SIZE / 2, MINIMAP_SIZE / 2};

		start = MINIMAP_SIZE / 2 - 30;
		size = MINIMAP_SIZE / 2 - 20;

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
	(minimap->xmax - minimap->xmin) * COEF_MINIMAP + MINIMAP_SIZE + 1,
	(minimap->ymax - minimap->ymin) * COEF_MINIMAP + MINIMAP_SIZE + 1)))
		return (0);
	draw_sectors(minimap->surface, &(env->engine)); // a proteger ?

	if (!(minimap->background = ui_make_surface(
	MINIMAP_SIZE + 1, MINIMAP_SIZE + 1)))
		return (0);
	draw_background(minimap->background);
	draw_player(minimap->background);
	draw_compass(minimap->background, env);

	return (1);
}
