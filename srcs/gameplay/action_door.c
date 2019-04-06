/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:07:36 by abaille           #+#    #+#             */
/*   Updated: 2019/04/06 04:09:40 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	door_neighbors(t_engine *e, const t_vtx *vertex, int s)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)e->nsectors)
	{
		if (e->sectors[i].is_door)
		{
			j = -1;
			while (++j < (int)e->sectors[i].npoints)
			{
				if (equal_vertex(vertex[s], e->sectors[i].vertex[j]))
				{
					j = -1;
					while (++j < (int)e->sectors[i].npoints)
					{
						if (equal_vertex(vertex[s + 1], e->sectors[i].vertex[j]))
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
			sect->vertex[s]) < 5 && sect->is_door)
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
		if (!env->stats.nb_enemies)
			sector->door.is_openable = 1;
		if (sector->door.is_openable && !sector->door.is_open)
			sector->door.is_opening = 1;
	}
	return (1);
}

int	handle_doors(t_env *env)
{
	t_sector	*sector;
	int			index;

	if ((index = select_door(&env->engine)) > -1)
	{
		sector = &env->engine.sectors[index];
		if (sector->door.is_openable && sector->door.is_opening
		&& !sector->door.is_open && sector->ceil > 0)
		{
			sector->ceil = (int)(sector->ceil - 1) % 39;
			sector->door.frame++;
		}
		else if (sector->door.is_open && sector->door.is_opening
		&& sector->ceil < 41)
		{
			sector->ceil = (int)(sector->ceil + 1) % 41;
			sector->door.frame++;
		}
		else if (!sector->door.is_openable)
			draw_scaled_string((t_font){WHITE, "Can t open yet",
			env->hud.text.text, (t_vtx){W / 2, H / 2}, W / 40, -1, -1},
			env->hud.text.doors[1], env->sdl.surface, (t_vtx){0, 0});
		else if (!sector->door.is_open)
		{
			draw_scaled_string((t_font){WHITE, "Press E",
			env->hud.text.text, (t_vtx){W / 2, H / 2}, W / 40, -1, -1},
			env->hud.text.doors[0], env->sdl.surface, (t_vtx){0, 0});
		}
		else
		{
			sector->door.is_open = !sector->door.is_open;
			sector->door.is_opening = 0;
			sector->door.frame = 0;
		}
	}
	return (1);
}