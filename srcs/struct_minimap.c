/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 11:57:31 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/27 13:38:58 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_init_minimap(t_env *env)
{
	env->minimap.origin.x = env->height - (env->width / 4) - 10;
	env->minimap.origin.y = 10;
	env->minimap.centre.x = (env->width - (env->width / 4) / 2) - 10;
	env->minimap.centre.y = (env->height / 4) / 2 + 10;
	env->minimap.map_size.w = env->minimap.mnp_size * 24; // to set relative
	env->minimap.map_size.h = env->minimap.mnp_size * 24; // tp set relative
	env->minimap.pos_play.x = env->pos.x * env->minimap.mnp_size;
	env->minimap.pos_play.y = env->pos.y * env->minimap.mnp_size;
	env->minimap.diff.x = env->minimap.centre.x - env->minimap.pos_play.x;
	env->minimap.diff.y = env->minimap.centre.y - env->minimap.pos_play.y;
	env->minimap.limit.l = env->minimap.origin.x;
	env->minimap.limit.r = env->width - env->minimap.origin.y;
	env->minimap.limit.t = 10;
	env->minimap.limit.b = env->height / 4 + 10;
}

static void		ft_draw_background(t_data *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){data->minimap.origin.x,
	data->minimap.origin.y, env->width / 4, env->height / 4};
	//ft_draw_border(rect, 0xFFFFFFFF, env);
	//ft_draw_rect(rect, 0xFF000000, &(env->minimap.limit), env);
}

static void		ft_draw_ray(int i, int j, t_env *env)
{
	double		angle_r;
	t_point		step;
	t_point		a;
	t_point		b;

	angle_r = (data->thread[i].ray[j].angle_d) * M_PI / 180;
	step.x = -cos(angle_r) * (data->thread[i].ray[j].dist_minimap)
	* data->minimap.mnp_size / 50;
	step.y = -sin(angle_r) * (data->thread[i].ray[j].dist_minimap)
	* data->minimap.mnp_size / 50;
	a = (t_pos){data->minimap.centre.x, data->minimap.centre.y};
	b.x = data->minimap.centre.x + step.x;
	b.y = data->minimap.centre.y + step.y;
	draw_line(data, a, b, 0xFFBFFCFF, &(data->minimap.limit));
}

static void		ft_draw_player(t_env *env)
{
	SDL_Rect	player;
	int			i;
	int			j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < env->width / 8)
		{
			ft_draw_ray(i, j, env); // foreach (line) ->wdist
			j++;
		}
		i++;
	}
	player = (SDL_Rect){env->minimap.centre.x - 5,
	env->minimap.centre.y - 5, 10, 10};
	ft_draw_rect(player, 0x0, 0, env);
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
			if (env->wmap[i][j] & 0x10)
				surface_drawrect(env->sdl.surface, rect, 0xFF5C4424);
				//surface_drawrect(rect, 0xFF5C4424, &(data->minimap.limit), data);
			else
				surface_drawrect(env->sdl.surface, rect, 0xFFADADAD);
				//ft_draw_rect(rect, 0xFFADADAD, &(data->minimap.limit), data);
			j++;
		}
		i++;
	}
	ft_draw_player(env);
}
