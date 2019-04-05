/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_wheel_hud.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:15 by abaille           #+#    #+#             */
/*   Updated: 2019/04/05 12:34:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     wpn_mouse_wheel(t_env *env, SDL_Event event)
{
	t_inventory *inventory;
	int         *wheel;

	inventory = &env->player.inventory;
	wheel = &env->hud.inventory.wwheel;
	if (event.type == SDL_MOUSEWHEEL)
	{
		if (inventory->current)
		{
			if (event.wheel.y > 0 && *wheel < WORLD_NB_WEAPONS)
			{
				(*wheel)++;
				*wheel = *wheel > WORLD_NB_WEAPONS
				? WORLD_NB_WEAPONS - 1 : *wheel;
				if (env->player.inventory.weapons[*wheel].current)
					set_current_wpn(inventory, *wheel);
			}
			else if (event.wheel.y < 0 && *wheel > 0)
			{
				(*wheel)--;
				*wheel = *wheel < 0 ? 0 : *wheel;
				if (env->player.inventory.weapons[*wheel].current)
					set_current_wpn(inventory, *wheel);
			}
		}
	}
	return (1);
}