/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:36:33 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/05 17:38:47 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void        weapon_bzero(t_weapon *new)
{
    new->sprite = NULL;
    new->sprite_bullet = NULL;
    new->sprite_reload = NULL;
    new->sprite_shoot = NULL;
    new->time_reload = 0;
    new->time_shoot = 0;
    new->time_shoot_between = 0;
    new->ammo_current = 0;
    new->ammo_magazine = 0;
    new->ammo_max = 0;
    new->damage = 0;
}

t_weapon *weapon_new(void)
{
    t_weapon *new;

    if ((t_weapon *)(malloc(sizeof(t_weapon))) == NULL)
        return (NULL);
    weapon_bzero(new);
    return (new);
}