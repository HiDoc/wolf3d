/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 21:49:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int init_hud_objects(t_hud *hud, char *res)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (!(hud->objects[i] = ui_img(res, "hud/", "objects/", i)))
            return (0);
        hud->shortcut[i] = NULL;
        i++;
    }
    return (1);
}

int init_hud_faces(t_hud *hud, char *res)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (!(hud->faces[i] = ui_img(res, "hud/", "faces/", i)))
            return (0);
        i++;
    }
    return (1);
}

int init_hud_wpn(t_hud *hud, char *res)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (!(hud->hud_wpn[i] = ui_img(res, "hud/", "wpn/", i)))
            return (0);
        i++;
    }
    return (1);
}

int init_hud_barhp(t_hud *hud, char *res)
{
    if ((hud->bar[0] = ui_img(res, "hud/", "hpbars/", 0))
    && (hud->bar[1] = ui_img(res, "hud/", "hpbars/", 1)))
        return (1);
    return (0);
}

int init_hud(t_env *env, char *res)
{
    if (!(env->player.hud.empty_b = ui_img(res, "hud/", "box/", 0)))
        return (0);
    return (init_hud_faces(&env->player.hud, res)
    && init_hud_barhp(&env->player.hud, res)
    && init_hud_objects(&env->player.hud, res)
    && init_hud_wpn(&env->player.hud, res));
}
