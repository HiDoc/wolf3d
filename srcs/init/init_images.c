/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:23:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/01 14:33:26 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_pack_img(t_surface *pack, char *name, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pack[i].sprite = ui_img(name, i);
		i++;
	}
}

static void			init_consumable(t_env *env)
{
	int 		i;
	char		*name;
	const char	*tab[WORLD_NB_OBJECTS] = {N_HEALTH, N_SHIELD, N_AMMO_M_R,
	N_AMMO_S, N_AMMO_R, N_JETPACK, N_GEM_B, N_GEM_G, N_GEM_R, N_GEM_P, N_MAGNUM,
	N_SHOTGUN, N_RIFLE, N_RPG};

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		name = ft_strjoin("consumable/", tab[i]);
		name = ft_strljoin(name, "+");
		if (i < WORLD_NB_CSMBLE)
		{
			env->world.objects[i].max_stack = (i == 5) ? 1 : 5;
			env->world.objects[i].size = (t_l_float){8, 3};
		}
		else if (i > WORLD_NB_CSMBLE + WORLD_NB_GEMS)
		{
			env->world.objects[i].max_stack = 0;
			env->world.objects[i].size = (t_l_float){7, 2};
		}
		else
		{
			env->world.objects[i].max_stack = -1;
			env->world.objects[i].size = (t_l_float){6, 1};
		}
		env->world.objects[i].sprite = ui_img(name, i);
		lt_release(name);
		i++;
	}
	env->hud.inventory.is_active = 0;
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
	printf("time consumable: %u\n", SDL_GetTicks());
}

static void			init_character(t_character *new)
{
	ft_bzero(&new->actions, sizeof(new));
	new->max_health = 200;
	new->max_shield = 200;
}

static void			init_skybox_img(t_env *env)
{
	env->skybox.sb_top = load_image("rsrc/skybox/sb_top.jpg");
	env->skybox.sb = load_image("rsrc/skybox/sb.jpg");
}

void				load_images(t_env *env)
{
	init_pack_img(env->world.surfaces.poster, "posters/", WORLD_NB_POSTERS);
	init_pack_img(env->world.surfaces.walls, "walls/", WORLD_NB_WALLS);
	init_pack_img(env->world.surfaces.floors, "floors/", WORLD_NB_FLOORS);
	init_pack_img(env->world.surfaces.hud, "hud/", NB_HUD_OBJ);
	init_pack_img(env->world.surfaces.img_menu, "menu/", NB_IMG_MENU);
	init_consumable(env);
	init_character(&env->player);
	init_skybox_img(env);
	env->engine.player.sprite = ui_img("bullet/", 0);
}
