/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:59 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 14:35:10 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     init_character(t_character *new)
{
    ft_bzero(&new->actions, sizeof(new));
    new->health = 200;
    new->shield = 200;
    new->max_health = 200;
    new->max_shield = 200;
    new->hud.is_txt = 0;
    return (1);
}