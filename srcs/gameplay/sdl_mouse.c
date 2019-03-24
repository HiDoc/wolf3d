/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/24 13:15:34 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	mouse_shoot(t_env *env)
{
	t_weapon	*rwpn;

	if (env->sdl.event.type == SDL_MOUSEBUTTONDOWN
	&& env->player.inventory.current
	&& !env->player.hud.inventory.is_active
	&& !env->player.actions.is_loading
	&& !env->player.actions.mouse_state)
	{
		rwpn = &env->world.armory[env->player.inventory.current->current->ref];
		if (env->player.inventory.current->ammo_current)
		{
			env->player.actions.is_shooting = !env->player.actions.is_shooting;
			env->player.actions.mouse_state = rwpn->time_shoot_between;
			// Mix_PlayChannel(0,	rwpn->shot,	0);
			env->player.inventory.current->ammo_current--;
		}
		else
		{
			load_weapon(env);
			env->player.actions.mouse_state = 1;
		}
	}
	if (env->sdl.event.type == SDL_MOUSEBUTTONUP && !env->time.frame)
		env->player.actions.mouse_state = 0;
	return (0);
}
