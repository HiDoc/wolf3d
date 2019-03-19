/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 13:37:13 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	mouse_shoot(t_env *env)
{
	if (env->sdl.event.type == SDL_MOUSEBUTTONDOWN
	&& env->player.inventory.current
	&& !env->player.inventory.ui.is_active
	&& !env->player.actions.is_loading
	&& !env->player.actions.mouse_state)
	{
		if (env->player.inventory.current->ammo_current)
		{
			env->player.actions.is_shooting = !env->player.actions.is_shooting;
			env->player.actions.mouse_state = 1;
			Mix_PlayChannel(-1,
			env->world.armory[env->player.inventory.current->current->ref].shot,
			0);
			env->player.inventory.current->ammo_current--;
		}
		else
			load_weapon(env);
	}
	if (env->sdl.event.type == SDL_MOUSEBUTTONUP)
		env->player.actions.mouse_state = 0;
	return (0);
}