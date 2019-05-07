/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_wheel_hud.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:15 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 19:35:14 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wpn_mouse_wheel(t_env *env, SDL_Event event)
{
	t_inventory	*inventory;
	int			*wheel;

	inventory = &env->player.inventory;
	wheel = &env->hud.inventory.wwheel;
	if (event.type == SDL_MOUSEWHEEL)
	{
		if (inventory->current->is_full)
		{
			if (event.wheel.y > 0 && *wheel < WORLD_NB_WEAPONS)
			{
				(*wheel)++;
				if (env->player.inventory.weapons[*wheel].is_full)
					set_current_wpn(env, inventory, *wheel);
				*wheel = *wheel > GAME_NB_WPN
				? GAME_NB_WPN : *wheel;
			}
			else if (event.wheel.y < 0 && *wheel > 0)
			{
				(*wheel)--;
				if (env->player.inventory.weapons[*wheel].is_full)
					set_current_wpn(env, inventory, *wheel);
				*wheel = (*wheel < 0) ? 0 : *wheel;
			}
		}
	}
}
