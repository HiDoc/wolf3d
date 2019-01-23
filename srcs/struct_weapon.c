/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:36:33 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/23 20:45:38 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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

void weapon_set(t_weapon *weapon, char *name)
{
    char *r_path;
    char *s_path;
    char *sprite;
    long ref;

    ref = weapon->ref;
    weapon->type = (ref & 0xF);
    weapon->time_reload = weapon_mask(ref, 1);
    weapon->time_shoot = weapon_mask(ref, 3);
    weapon->time_shoot_between = weapon_mask(ref, 5);
    weapon->ammo_current = weapon_mask(ref, 7);
    weapon->ammo_magazine = weapon_mask(ref, 9);
    weapon->damage = ((ref & (0xF << 11)) >> 11);
    r_path = ft_strjoin(name, "/reload/");
    s_path = ft_strjoin(name, "/shoot/");
    sprite = ft_strjoin(name, "/");
    sprite = ft_strljoin(sprite, name);
    weapon->sprite = img_wpn(sprite);
    weapon->sprite_reload = weapon_fill(r_path, weapon->time_reload);
    weapon->sprite_shoot = weapon_fill(s_path, weapon->time_shoot);
    free(r_path);
    free(s_path);
    free(sprite);
}

t_weapon *weapon_new(void)
{
    t_weapon *new;

    if ((new = (t_weapon *)(malloc(sizeof(t_weapon)))) == NULL)
        return (NULL);
    ft_bzero(new, sizeof(t_weapon));
    return (new);
}