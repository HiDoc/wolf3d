/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 11:57:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/21 14:37:03 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_init_minimap(t_env *env)
{
	env->minimap.origin.x = env->sdl.width - (env->sdl.width / 4) - 10;
	env->minimap.origin.y = 10;
	env->minimap.centre.x = (env->sdl.width - (env->sdl.width / 4) / 2) - 10;
	env->minimap.centre.y = (env->sdl.height / 4) / 2 + 10;
	env->minimap.map_size.x = env->minimap.mnp_size * env->map_w;
	env->minimap.map_size.y = env->minimap.mnp_size * env->map_h;
	env->minimap.pos_play.x = env->player.pos.y * env->minimap.mnp_size;
	env->minimap.pos_play.y = env->player.pos.x * env->minimap.mnp_size;
	env->minimap.diff.x = env->minimap.centre.x - env->minimap.pos_play.x;
	env->minimap.diff.y = env->minimap.centre.y - env->minimap.pos_play.y;
	env->minimap.limit.xmin = env->minimap.origin.x;
	env->minimap.limit.xmax = env->sdl.width - env->minimap.origin.y;
	env->minimap.limit.ymin = 10;
	env->minimap.limit.ymax = env->sdl.height / 4 + 10;
}

/*static*/ void		ft_draw_background(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){env->minimap.origin.x,
	env->minimap.origin.y, env->sdl.width / 4, env->sdl.height / 4};
	surface_drawrect(env->sdl.surface, rect, 0, 0xFF000000);
	surface_drawborder(env->sdl.surface, rect, 0xFFFFFFFF);
}

/*static*/ void		ft_draw_ray(int i, t_env *env)
{
	t_limit		l;

	l = (t_limit){env->minimap.centre.x, env->minimap.centre.x
	+ (env->rays[i].line.raydir.y * env->rays[i].line.wdist * 20),
	env->minimap.centre.y,
	env->minimap.centre.y
	+ (env->rays[i].line.raydir.x * env->rays[i].line.wdist * 20)};
	surface_drawline_limit(env->sdl.surface, l, env->minimap.limit, 0xFFBFFCFF);
}

/*static*/ void		ft_draw_bots(t_env *env)
{
	t_point		calcpos;
	Uint32		color;
	SDL_Rect	rect;
	t_point		end;
	int			i;

	i = 0;
	while (i < env->nb_bots)
	{
		calcpos.x = env->minimap.diff.x
		+ (env->bots[i]->position.x * env->minimap.mnp_size) - 5;
		calcpos.y = env->minimap.diff.y
		+ (env->bots[i]->position.y * env->minimap.mnp_size) - 5;

		rect = (SDL_Rect){calcpos.x, calcpos.y, 10, 10};
		if (env->bots[i]->detected == 1)
			color = 0xFF0000FF;
		else if (env->bots[i]->alerted == 1)
			color = 0xFF3399FF;
		else
			color = 0xFF000000;

		// monster
		surface_drawrect(env->sdl.surface, rect, &(env->minimap.limit), color);

		// monster direction
		calcpos.x += 5;
		calcpos.y += 5;
		/*end.x = calcpos.x + cos(env->bots[i]->direction * M_PI / 180)
		* env->bots[i]->player_dist * env->minimap.mnp_size;
		end.y = calcpos.y + sin(env->bots[i]->direction * M_PI / 180)
		* env->bots[i]->player_dist * env->minimap.mnp_size;
		surface_drawline_limit(env->sdl.surface, calcpos, end,
		env->minimap.limit, color);*/

		// debug
		end.x = calcpos.x + env->bots[i]->debug.x * env->minimap.mnp_size;
		end.y = calcpos.y + env->bots[i]->debug.y * env->minimap.mnp_size;
		t_limit l = (t_limit){calcpos.x, end.x, calcpos.y, end.y};
		surface_drawline_limit(env->sdl.surface, l,
		env->minimap.limit, color);

		i++;
	}
}

/*static*/ void		ft_draw_player(t_env *env)
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

void	ui_put_minimap(t_env *env)
{
	SDL_Rect	rect;
	int			i;
	int			j;

	ft_init_minimap(env);
	ft_draw_background(env);
	i = 0;
	while (i < env->map_h)
	{
		j = 0;
		while (j < env->map_w)
		{
			rect = (SDL_Rect){env->minimap.diff.x + (j * env->minimap.mnp_size),
			env->minimap.diff.y + (i * env->minimap.mnp_size),
			env->minimap.mnp_size, env->minimap.mnp_size};
			if (env->w_map[i][j] & 0x00000010)
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
