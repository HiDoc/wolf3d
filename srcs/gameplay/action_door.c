/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:07:36 by abaille           #+#    #+#             */
/*   Updated: 2019/04/08 01:33:20 by abaille          ###   ########.fr       */
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

int	open_door(t_env *env)
{
	int	index;
	t_sector	*sector;

	if ((index = select_door(&env->engine)) > -1)
	{
		sector = &env->engine.sectors[index];
		if (sector->door.is_openable)
			sector->door.is_opening = 1;
	}
	return (1);
}

int	print_infos_door(t_env *env, t_sector *sector)
{
	int			index;
	t_door		*front_player;

	if ((index = select_door(&env->engine)) > -1)
	{
		front_player = &sector[index].door;
		if (!front_player->is_openable)
			draw_scaled_string((t_font){WHITE, "Can t open yet",
			env->hud.text.text, (t_vtx){W / 2, H / 2}, W / 40, -1, -1},
			env->hud.text.doors[1], env->sdl.surface, (t_vtx){0, 0});
		else if (!front_player->is_open && !front_player->is_opening)
		{
			draw_scaled_string((t_font){WHITE, "Press E",
			env->hud.text.text, (t_vtx){W / 2, H / 2}, W / 40, -1, -1},
			env->hud.text.doors[0], env->sdl.surface, (t_vtx){0, 0});
		}
	}
	return (1);
}

int	handle_doors(t_env *env)
{
	t_sector	*sector;
	int			i;

	i = -1;
	sector = env->engine.sectors;
	while (++i < (int)env->engine.nsectors)
	{
		if (sector[i].is_door
		&& (sector[i].door.is_openable || !env->stats.nb_enemies))
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
	return (print_infos_door(env, sector));
}