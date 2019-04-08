/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:23:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 23:51:06 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_pack_img(t_surface *pack, char *name, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (!(pack[i].sprite = ui_img(name, i)))
			doom_error_exit("Doom_nukem error ???");
		i++;
	}
}

static void		load_enemies(t_world *container)
{

	int		i;
	int		j;

	i = 0;
	while (i < WORLD_NB_ENEMIES)
	{
		j = 0;
		while (j < 6)
		{
			if (!(container->enemies[i].sprites[j]=ui_img("enemies/suitguy/", j)))
				doom_error_exit("Doom_nukem error ???");
			j++;
		}
		i++;
	}
}

static void			init_consumable(t_env *env)
{
	int i;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_CSMBLE)
		{
			env->world.objects[i].max_stack = (i == 5) ? 1 : 5;
			if (!(env->world.objects[i].sprite = ui_img("consumable/", i)))
				doom_error_exit("Doom_nukem error ???");
		}
		else if (i > WORLD_NB_CSMBLE + WORLD_NB_GEMS)
		{
			env->world.objects[i].max_stack = 0;
			if (!(env->world.objects[i].sprite = ui_img("consumable/", i)))
				doom_error_exit("Doom_nukem error ???");
		}
		else
		{
			env->world.objects[i].max_stack = -1;
			if (!(env->world.objects[i].sprite = ui_img("consumable/", i)))
				doom_error_exit("Doom_nukem error ???");
		}
		i++;
	}
	env->hud.inventory.is_active = 0;
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
	printf("time consumable: %u\n", SDL_GetTicks());
}

static void			init_character(t_character *new)
{
	int i;

	i = -1;
	ft_bzero(&new->actions, sizeof(new));
	new->health = 200;
	new->shield = 200;
	new->max_health = 200;
	new->max_shield = 200;
	if (!(new->bullet = ui_img("bullet/", 0))
			|| !(new->shot = malloc(sizeof(t_impact) * PLYR_NB_SHOT)))
		doom_error_exit("Doom_nukem error ???");
	while (++i < PLYR_NB_SHOT)
		ft_bzero(&new->shot[i], sizeof(t_impact));
}

void				load_images(t_env *env)
{
	init_pack_img(env->world.surfaces.poster, "posters/", WORLD_NB_POSTERS);
	init_pack_img(env->world.surfaces.walls, "walls/", WORLD_NB_WALLS);
	init_pack_img(env->world.surfaces.floors, "floors/", WORLD_NB_FLOORS);
	init_pack_img(env->world.surfaces.hud, "hud/", NB_HUD_OBJ);
	load_enemies(&env->world);
	init_consumable(env);
	init_character(&env->player);
}
