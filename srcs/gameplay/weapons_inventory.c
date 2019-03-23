/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_inventory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:15 by abaille           #+#    #+#             */
/*   Updated: 2019/03/23 19:30:32 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     wpn_mouse_wheel(t_env *env, SDL_Event event)
{
    if (event.type == SDL_MOUSEWHEEL)
    {
        if (env->player.inventory.current)
        {
            if (event.wheel.y > 0 && env->player.hud.inventory.wwheel < env->player.hud.inventory.nb_wpn - 1)
            {
                env->player.hud.inventory.wwheel++;
                if (env->player.inventory.weapons[env->player.hud.inventory.wwheel].current)
                    env->player.inventory.current->current = env->player.inventory.weapons[env->player.hud.inventory.wwheel].current;
            }
            else if (event.wheel.y < 0 && env->player.hud.inventory.wwheel > 0)
            {
                env->player.hud.inventory.wwheel--;
                if (env->player.inventory.weapons[env->player.hud.inventory.wwheel].current)
                    env->player.inventory.current->current = env->player.inventory.weapons[env->player.hud.inventory.wwheel].current;
            }
        }
    }
    return (1);
}