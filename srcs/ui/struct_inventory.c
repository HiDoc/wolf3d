/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_inventory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:21 by abaille           #+#    #+#             */
/*   Updated: 2019/03/15 18:23:47 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     init_icon(t_env *env)
{
    if ((env->player.inventory.ui.icon[0] = ui_img("icons/icon_health"))
    && (env->player.inventory.ui.icon[1] = ui_img("icons/icon_shield")))
        return (1);
    // && (env->player.inventory.ui.icon[2] = ui_img("icons/icon_key"))

    return (0);
}

int     init_wpn_inv(t_env *env)
{
    if ((env->player.inventory.ui.mini_wpn[1] = ui_img("wpn/lmini_ak"))
    && (env->player.inventory.ui.mini_wpn[0] = ui_img("wpn/lmini_pistol"))
    && (env->player.inventory.ui.mini_wpn[2] = ui_img("wpn/lmini_rifle")))
        return (1);
    // && (env->player.inventory.ui.empt_wpn[0] = ui_img("wpn/empty_pistol"))
    // && (env->player.inventory.ui.empt_wpn[1] = ui_img("wpn/empty_ak"))
    // && (env->player.inventory.ui.empt_wpn[2] = ui_img("wpn/empty_rifle"))
    return (0);
}

int     init_inv_box(t_env *env)
{
    if((env->player.inventory.ui.box[0] = ui_img("box/full"))
    && (env->player.inventory.ui.box[1] = ui_img("box/empty")))
    {
        printf("size empty %i, %i\n", env->player.inventory.ui.box[0]->w, env->player.inventory.ui.box[0]->h);
        return (1);
    }
    return (0);
}

int    init_inventory_ui(t_env *env)
{
   	// t_rgba	rgba;

    env->player.inventory.ui.front_pic = ui_img("fond800");
    // set_surface_alpha(env->player.inventory.ui.front_pic, 50, &rgba);
	env->player.inventory.ui.wwheel = 0;
    env->player.inventory.ui.nb_wpn = 1;
    env->player.inventory.nb_current_obj = 0;
    printf("size empty ok\n");
    init_wpn_inv(env);
    init_icon(env);
    init_inv_box(env);
    return (1);
}
