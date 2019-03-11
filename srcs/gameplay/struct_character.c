/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:59 by abaille           #+#    #+#             */
/*   Updated: 2019/03/10 22:17:00 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     init_character(t_character *new)
{
    new->health = 50;
    new->shield = 0;
    new->max_weapons = 3;
    new->max_objects = 3;
    new->max_health = 200;
    new->max_shield = 200;
    new->hud.is_txt = 0;
    new->actions.sub_action = 0;
    new->actions.is_loading = 0;
    new->actions.is_shooting = 0;
    new->actions.is_flying = 0;
    return (0);
}