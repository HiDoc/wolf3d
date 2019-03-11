/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_inventory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:15 by abaille           #+#    #+#             */
/*   Updated: 2019/03/10 22:17:17 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     wpn_mouse_wheel(t_env *env, SDL_Event event)
{
    if (event.type == SDL_MOUSEWHEEL)
    {
        if (env->player.inventory.current)
        {
            if (event.wheel.y > 0 && env->player.inventory.ui.wwheel < env->player.inventory.ui.nb_wpn - 1)
            {
                if (env->player.inventory.weapons[env->player.inventory.ui.wwheel + 1].current)
                    env->player.inventory.current->current = env->player.inventory.weapons[++env->player.inventory.ui.wwheel].current;
            }
            else if (event.wheel.y < 0 && env->player.inventory.ui.wwheel > 0)
            {
                if (env->player.inventory.weapons[env->player.inventory.ui.wwheel - 1].current)
                    env->player.inventory.current->current = env->player.inventory.weapons[--env->player.inventory.ui.wwheel].current;
            }
        }
    }
    return (1);
}