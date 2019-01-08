/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:36:33 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/08 10:57:49 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_weapon *weapon_new(void)
{
    t_weapon *new;

    if ((t_weapon *)(malloc(sizeof(t_weapon))) == NULL)
        return (NULL);
    ft_bzero(new, sizeof(new));
    return (new);
}