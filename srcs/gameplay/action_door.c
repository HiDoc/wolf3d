/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:07:36 by abaille           #+#    #+#             */
/*   Updated: 2019/04/19 01:38:59 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	door_neighbors(t_engine *e, t_vtx *vertex, int n)
{
	t_sector	*sect;
	int			i;
	int			j;

	i = -1;
	while (++i < (int)e->nsectors)
	{
		sect = &e->sectors[i];
		j = -1;
		if (sect->is_door)
		{
			while (++j < (int)sect->npoints)
			{
				if (equal_vertex(vertex[n], sect->vertex[j]))
				{
					j = -1;
					while (++j < (int)sect->npoints)
					{
						if (equal_vertex(vertex[n + 1], sect->vertex[j]))
							return (1);
					}
				}
			}
		}
	}
	return (0);
}

int	select_door(t_engine *e)
{
	int			i;
	int			s;
	t_sector	*sect;

	i = -1;
	while (++i < (int)e->nsectors)
	{
		sect = &e->sectors[i];
		s = -1;
		while (++s < (int)sect->npoints)
		{
			if (dist_vertex((t_vtx){e->player.where.x, e->player.where.y},
			sect->vertex[s]) < 10 && sect->is_door)
				return (i);
		}
	}
	return (-1);
}

int		open_door(t_env *e)
{
	int			index;
	t_sector	*sector;
	int			sound;

	if ((index = select_door(&e->engine)) > -1)
	{
		sector = &e->engine.sectors[index];
		play_chunk(-1,	e->sound.s_effect[EFCT_BTNDOOR], 0);
		if (sector->door.is_openable)
		{
			sound = !sector->door.is_open ? EFCT_OP_LILDOOR : EFCT_CL_LILDOOR;
			play_chunk(-1,	e->sound.s_effect[sound], 0);
			sector->door.is_opening = 1;
		}
		else
			play_chunk(-1,	e->sound.s_effect[EFCT_DOORLOCK], 0);
	}
	return (1);
}

void	print_infos_door(t_env *env, t_sector *sector)
{
	int			index;
	t_door		*front_player;
	t_bloc		fill;

	if ((index = select_door(&env->engine)) > -1)
	{
		ft_bzero(&fill, sizeof(t_bloc));
		fill.rect = (SDL_Rect){W / 2, H / 2, env->hud.text.doors[1]->w, env->hud.text.doors[1]->h};
		front_player = &sector[index].door;
		if (!front_player->is_openable)
			draw_img(env, env->hud.text.doors[1], &fill);
		else if (!front_player->is_open && !front_player->is_opening)
			draw_img(env, env->hud.text.doors[0], &fill);
	}
}

void	handle_doors(t_env *env)
{
	t_sector	*sector;
	int			i;

	i = -1;
	sector = env->engine.sectors;
	while (++i < (int)env->engine.nsectors)
	{
		if (sector[i].is_door
		&& (sector[i].door.is_openable || !env->stats.data[I_KTOGO]))
		{
			sector[i].door.is_openable = 1;
			if (sector[i].door.is_opening
			&& !sector[i].door.is_open && sector[i].ceil < 40)
				sector[i].ceil = (int)(sector[i].ceil + 1) % 41;
			else if (sector[i].door.is_open
			&& sector[i].door.is_opening && sector[i].ceil > 0)
				sector[i].ceil = (int)(sector[i].ceil - 1) % 41;
			else if ((sector[i].ceil >= 40 || sector[i].ceil <= 0)
			&& sector[i].door.is_opening)
			{
				sector[i].door.is_open = !sector[i].door.is_open;
				sector[i].door.is_opening = 0;
			}
		}
	}
	print_infos_door(env, sector);
}