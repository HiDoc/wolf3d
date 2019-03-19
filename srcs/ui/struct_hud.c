/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 16:38:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int init_hud(t_env *env, int i)
{
    while (i < 6)
    {
        if (!(env->player.hud.objects[i] = ui_img("hud/", "objects/", i)))
            return (0);
        if (i < 4)
        {
            if (!(env->player.hud.faces[i] = ui_img("hud/", "faces/", i)))
                return (0);
        }
        if (i < 3)
        {
            if (!(env->player.hud.hud_wpn[i] = ui_img("hud/", "wpn/", i)))
                return (0);
        }
        if (i < 2)
        {
            if (!(env->player.hud.bar[i] = ui_img("hud/", "hpbars/", i)))
                return (0);
        }
        env->player.hud.shortcut[i++] = NULL;
    }
    if (!(env->player.hud.empty_b = ui_img("hud/", "box/", 0)))
        return (0);
    return (1);
}
