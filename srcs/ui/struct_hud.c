/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 15:30:44 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int init_hud(t_env *env)
{
    int i;
    // t_rgba      rgb;
    // SDL_Surface *tmp;

    i = 0;
    env->player.hud.mix = 0;
    while (i < 6)
        env->player.hud.shortcut[i++] = NULL;
    env->player.hud.hud_wpn[0] = ui_img("hud/hud_pistol");
    if ((env->player.hud.bar[0] = ui_img("hud/bar_h"))
    && (env->player.hud.bar[1] = ui_img("hud/bar_s"))
    && (env->player.hud.hud_wpn[1] = ui_img("hud/hud_pompe"))
    && (env->player.hud.hud_wpn[2] = ui_img("hud/hud_rifle"))
    && (env->player.hud.empty_b = ui_img("hud/hud_empty"))
    && (env->player.hud.full_b = ui_img("hud/hud_full"))
    && (env->player.hud.objects[0] = ui_img("hud/hud_health"))
    && (env->player.hud.objects[1] = ui_img("hud/hud_armor"))
    && (env->player.hud.objects[2] = ui_img("hud/hud_ammo1"))
    && (env->player.hud.objects[3] = ui_img("hud/hud_ammo2"))
    && (env->player.hud.objects[4] = ui_img("hud/hud_ammo3"))
    && (env->player.hud.objects[5] = ui_img("hud/hud_jetpack"))
    && (env->player.hud.faces[0] = ui_img("hud/hp_face1"))
    && (env->player.hud.faces[1] = ui_img("hud/hp_face2"))
    && (env->player.hud.faces[2] = ui_img("hud/hp_face3"))
    && (env->player.hud.faces[3] = ui_img("hud/hp_face4")))
        return (1);
    return (0);
}
