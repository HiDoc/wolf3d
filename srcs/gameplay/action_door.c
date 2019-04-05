/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:07:36 by abaille           #+#    #+#             */
/*   Updated: 2019/04/05 20:04:31 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	front_door(t_env *env)
{
	int	s;
	int	i;
	t_sector	*sect;
	t_vtx		*vert;

	i = -1;
	while (++i < (int)env->engine.nsectors)
	{
		sect = &env->engine.sectors[i];
		vert = sect->vertex;
		s = -1;
		while (++s < (int)sect->npoints)
		{
			if (dist_vertex((t_vtx){env->engine.player.where.x, env->engine.player.where.y}, vert[s]) < 5
			&& sect->is_door)
			{
				if (!sect->door.is_open)
				{
					printf("door is op %i\n", sect->door.is_open);
					if (sect->door.is_openable)
						draw_scaled_string((t_font){WHITE, "Open the door",
						env->hud.text.text, (t_vtx){W / 2, H / 2}, W / 40, -1, -1},
						env->hud.text.doors[0], env->sdl.surface, (t_vtx){0, 0});
					else
						draw_scaled_string((t_font){WHITE, "Can't open the door",
						env->hud.text.text, (t_vtx){W / 2, H / 2}, W / 40, -1, -1},
						env->hud.text.doors[1], env->sdl.surface, (t_vtx){0, 0});
				}
			}
		}
	}
	return (1);
}

int	open_door(t_env *env, t_door *door)
{
	return (1);
}