/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_inventory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:15 by abaille           #+#    #+#             */
/*   Updated: 2019/03/29 19:36:47 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     wpn_mouse_wheel(t_env *env, SDL_Event event)
{
	t_wrap_wpn  *current;
    int         *wheel;

    current = env->player.inventory.current;
    wheel = &env->hud.inventory.wwheel;
    if (event.type == SDL_MOUSEWHEEL)
    {
        if (current)
        {
            if (event.wheel.y > 0 && *wheel < env->hud.inventory.nb_wpn - 1)
            {
                (*wheel)++;
                if (env->player.inventory.weapons[*wheel].current)
                    current->current = env->player.inventory.weapons[*wheel].current;
            }
            else if (event.wheel.y < 0 && *wheel > 0)
            {
                (*wheel)--;
                if (env->player.inventory.weapons[*wheel].current)
                    current->current = env->player.inventory.weapons[*wheel].current;
            }
        }
    }
    return (1);
}