/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 11:57:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/01/05 17:57:01 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_init_minimap(t_env *env)
{
	env->minimap.origin.x = env->width - (env->width / 4) - 10;
	env->minimap.origin.y = 10;
	env->minimap.centre.x = (env->width - (env->width / 4) / 2) - 10;
	env->minimap.centre.y = (env->height / 4) / 2 + 10;
	env->minimap.map_size.x = env->minimap.mnp_size * 24; // to set relative
	env->minimap.map_size.y = env->minimap.mnp_size * 24; // tp set relative
	env->minimap.pos_play.x = env->pos.y * env->minimap.mnp_size;
	env->minimap.pos_play.y = env->pos.x * env->minimap.mnp_size;
	env->minimap.diff.x = env->minimap.centre.x - env->minimap.pos_play.x;
	env->minimap.diff.y = env->minimap.centre.y - env->minimap.pos_play.y;
	env->minimap.limit.xmin = env->minimap.origin.x;
	env->minimap.limit.xmax = env->width - env->minimap.origin.y;
	env->minimap.limit.ymin = 10;
	env->minimap.limit.ymax = env->height / 4 + 10;
}

static void		ft_draw_background(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){env->minimap.origin.x,
	env->minimap.origin.y, env->width / 4, env->height / 4};
	surface_drawrect(env->sdl.surface, rect, 0, 0xFF000000);
	surface_drawborder(env->sdl.surface, rect, 0xFFFFFFFF);
}

static void		ft_draw_ray(int i, t_env *env)
{
	t_point		a;
	t_point		b;

	// calcul des points
	a = (t_point){env->minimap.centre.x, env->minimap.centre.y};
	b.x = env->minimap.centre.x
	+ (env->rays[i].line.raydir.y * env->rays[i].line.wdist * 20);
	b.y = env->minimap.centre.y
	+ (env->rays[i].line.raydir.x * env->rays[i].line.wdist * 20);

	// affichage rayon
	surface_drawline_limit(env->sdl.surface, a, b,
	env->minimap.limit, 0xFFBFFCFF);
}

static void		ft_draw_bots(t_env *env)
{
	SDL_Rect	rect;
	int			i;

	i = 0;
	while (i < 1) // to set relative (nb of bots)
	{
		rect = (SDL_Rect)
		{env->minimap.diff.x
		+ (env->bots[i]->position.x * env->minimap.mnp_size),
		env->minimap.diff.y
		+ (env->bots[i]->position.y * env->minimap.mnp_size),
		10, 10};
		surface_drawrect(env->sdl.surface, rect, &(env->minimap.limit), 0x0);
		i++;
	}
}

static void		ft_draw_player(t_env *env)
{
	SDL_Rect	player;
	int			i;

	i = 0;
	while (i < WIDTH)
	{
		ft_draw_ray(i, env);
		i++;
	}
	player = (SDL_Rect){env->minimap.centre.x - 5,
	env->minimap.centre.y - 5, 10, 10};
	surface_drawrect(env->sdl.surface, player, 0, 0x00000000);
}

void	struct_minimap(t_env *env)
{
	SDL_Rect	rect;
	int			i;
	int			j;

	ft_init_minimap(env);
	ft_draw_background(env);
	i = 0;
	while (i < 24) // to set relative
	{
		j = 0;
		while (j < 24) // to set relative
		{
			rect = (SDL_Rect){env->minimap.diff.x + (j * env->minimap.mnp_size),
			env->minimap.diff.y + (i * env->minimap.mnp_size),
			env->minimap.mnp_size, env->minimap.mnp_size};
			if (env->w_map[i][j] & 0x0010)
				surface_drawrect(env->sdl.surface, rect,
				&(env->minimap.limit), 0xFF5C4424);
			else
				surface_drawrect(env->sdl.surface, rect,
				&(env->minimap.limit), 0xFFADADAD);
			j++;
		}
		i++;
	}
	ft_draw_player(env);
	ft_draw_bots(env);
}
