/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_inventory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:15 by abaille           #+#    #+#             */
/*   Updated: 2019/04/04 12:44:10 by abaille          ###   ########.fr       */
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
			if (event.wheel.y > 0 && *wheel < 5)
			{
				(*wheel)++;
				if (env->player.inventory.weapons[*wheel].current)
					set_current_wpn(inventory, *wheel);
			}
			else if (event.wheel.y < 0 && *wheel > 0)
			{
				(*wheel)--;
				if (env->player.inventory.weapons[*wheel].current)
					set_current_wpn(inventory, *wheel);
			}
		}
	}
	return (1);
}