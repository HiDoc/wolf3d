/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:20:50 by abaille           #+#    #+#             */
/*   Updated: 2019/03/17 17:19:33 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int weapon_mask(long ref, int pos)
{
    return (((ref >> (pos << 2)) & 0xFF));
}

/*
** Protect this area
** from null malloc
*/

SDL_Surface **weapon_fill(char *path, int size)
{
    int     i;
    SDL_Surface **weapons;
    char    *filename;

    i = 0;
    if ((weapons = malloc(sizeof(SDL_Surface *) * size)) == NULL)
        return (NULL);
    while (i < size)
    {
        filename = ft_strrjoin((char *)path, ft_itoa(i + 1));
        weapons[i] = img_wpn(filename);
        free(filename);
        filename = NULL;
        i++;
    }
    return (weapons);
}

void weapon_set(t_weapon *weapon, char *name, int dam)
{
    char *r_path;
    char *sprite;
    char *shoot;
    long ref;

    ref = weapon->ref;
    weapon->type = (ref & 0xF);
    weapon->time_reload = weapon_mask(ref, 1);
    weapon->time_shoot = weapon_mask(ref, 3);
    weapon->time_shoot_between = weapon_mask(ref, 5);
    weapon->ammo_curr_max = weapon_mask(ref, 7);
    weapon->ammo_mag_max = weapon_mask(ref, 9);
    weapon->ammo_current = weapon_mask(ref, 7);
    weapon->ammo_magazine = weapon_mask(ref, 9);
    weapon->damage = dam;
    r_path = ft_strjoin(name, "/reload/");
    sprite = ft_strjoin(name, "/");
    sprite = ft_strljoin(sprite, name);
    shoot = ft_strjoin(name, "/");
    shoot = ft_strjoin(shoot, "shoot");
    weapon->sprite = img_wpn(sprite);
    weapon->sprite_reload = weapon_fill(r_path, weapon->time_reload);
    weapon->sprite_shoot = img_wpn(shoot);
    free(r_path);
    free(sprite);
    free(shoot);
}

int		init_weapon(t_env *env)
{
    int i;

    i = 0;
	env->world.armory[0].ref = 0xa2a0602012a2;
	env->world.armory[1].ref = 0xa2a020201123;
	env->world.armory[2].ref = 0xa8e2002012f4;
	weapon_set(&env->world.armory[0], "pistol", 17);
	weapon_set(&env->world.armory[1], "pompe", 100);
	weapon_set(&env->world.armory[2], "rifle", 30);
    while (i < 3)
        env->player.inventory.weapons[i++].current = NULL;
    env->player.inventory.current = NULL;
    env->player.inventory.weapons[1].current = env->engine.sectors[0].head_object;
    env->player.inventory.current = &env->player.inventory.weapons[1];
    env->player.inventory.current->ammo_current = 50;
    env->player.inventory.current->ammo_magazine = 100;
    return (0);
}