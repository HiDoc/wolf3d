/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:07:40 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/05 16:29:27 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		load_enemies(t_world *container)
{
	int		i;
	int		j;
	// char	*tmp;
	// int		ret;

	i = 0;
	// ret = 0;
	while (i < WORLD_NB_ENEMIES)
	{
		j = 0;
			// printf("i %i\n", i);
		while (j < 6)
		{
		// tmp = NULL;
		// if ((tmp = ft_itoa(i) && tmp = (ft_strrjoin("enemies/", tmp))
			if (!(container->enemies[i].sprites[j] = ui_img("enemies/suitguy/", j)))
				return (0);
			// printf("sprite init\n");
			// printf("j %i\n", j);
		// 	ret = 1;
		// else
		// 	ret = 0;
		// if (tmp)
		// 	free(tmp);
		// if (!ret)
			j++;
		}
		i++;
	}
	return (1);
}

int	init_pack_img(t_surface *pack, char *name, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (!(pack[i].sprite = ui_img(name, i)))
			return (0);
		i++;
	}
	return (1);
}

int		init_container(t_env *env)
{
	t_container	*surface;

	surface = &env->world.surfaces;
	return (init_pack_img(env->world.surfaces.poster, "posters/",
	WORLD_NB_POSTERS)
	&& init_pack_img(env->world.surfaces.walls, "walls/",
	WORLD_NB_WALLS)
	&& init_pack_img(env->world.surfaces.floors, "floors/",
	WORLD_NB_FLOORS)
	&& init_pack_img(env->world.surfaces.hud, "hud/",
	NB_HUD_OBJ)
	&& load_enemies(&env->world));
}
