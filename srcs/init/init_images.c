/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:23:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 02:27:33 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_pack_img(t_surface *pack, char *name, int limit, int var)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pack[i].sprite = ui_img(name, i, var);
		i++;
	}
}

static void	infos_consumables(t_object *obj, int i)
{
	if (i < WORLD_NB_CSMBLE)
	{
		obj->max_stack = (i == 5) ? 1 : 5;
		obj->size = (t_l_float){8, 3};
	}
	else if (i > WORLD_NB_CSMBLE + WORLD_NB_GEMS)
	{
		obj->max_stack = 0;
		obj->size = (t_l_float){7, 2};
	}
	else
	{
		obj->max_stack = -1;
		obj->size = (t_l_float){6, 1};
	}
}

static void	init_consumable(t_env *env)
{
	int 		i;
	char		*name;
	const char	*tab[WORLD_NB_OBJECTS] = {N_HEALTH, N_SHIELD, N_AMMO_M_R,
		N_AMMO_S, N_AMMO_R, N_JETPACK, N_GEM_B, N_GEM_G, N_GEM_R, N_GEM_P,
		N_MAGNUM, N_SHOTGUN, N_RIFLE, N_RPG};

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		name = ft_strjoin("consumable/", tab[i]);
		name = ft_strljoin(name, "+");
		infos_consumables(&env->world.objects[i], i);
		env->world.objects[i].sprite = ui_img(name, i, 0);
		lt_release((void**)&name);
		i++;
	}
	env->hud.inventory.is_active = 0;
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
}

static void	init_character(t_character *new)
{
	ft_bzero(&new->actions, sizeof(new));
	new->max_health = 200;
	new->max_shield = 200;
}

static void	init_skybox_img(t_env *env)
{
	env->skybox.sb = load_image("rsrc/skybox/bluesky+0.jpg");
}

void		load_images(t_env *env)
{
	init_pack_img(env->world.surfaces.walls, "walls/", WORLD_NB_WALLS, 1);
	init_pack_img(env->world.surfaces.poster, "posters/", WORLD_NB_POSTERS, 1);
	init_pack_img(env->world.surfaces.floors, "floors/", WORLD_NB_FLOORS, 1);
	init_pack_img(env->world.surfaces.hud, "hud/", NB_HUD_OBJ, 0);
	init_pack_img(env->world.surfaces.img_menu, "menu/", NB_IMG_MENU, 0);
	init_consumable(env);
	init_character(&env->player);
	init_skybox_img(env);
	env->engine.player.sprite = ui_img("bullet/", 0, 0);
}
