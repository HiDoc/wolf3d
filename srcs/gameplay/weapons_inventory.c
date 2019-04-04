/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_inventory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:15 by abaille           #+#    #+#             */
/*   Updated: 2019/04/04 03:36:49 by abaille          ###   ########.fr       */
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
            if (event.wheel.y > 0 && *wheel < 5)
            {
                (*wheel)++;
                if (env->player.inventory.weapons[*wheel].current)
                    current->current = env->player.inventory.weapons[*wheel].current;
            }
            else if (event.wheel.y < 0 && *wheel > 0)
            {
                printf("valeur wheel %i \n", *wheel);
                printf("event wheel %i \n", event.wheel.y);
                (*wheel)--;
                if (env->player.inventory.weapons[*wheel].current)
                    current->current = env->player.inventory.weapons[*wheel].current;
            }
        }
    }
    return (1);
}