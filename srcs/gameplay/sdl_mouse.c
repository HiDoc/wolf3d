/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 21:09:49 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	mouse_shoot(t_env *env)
{
	t_weapon	*rwpn;

	if (env->sdl.event.type == SDL_MOUSEBUTTONDOWN
	&& env->player.inventory.current
	&& !env->player.inventory.ui.is_active
	&& !env->player.actions.is_loading
	&& !env->player.actions.mouse_state)
	{
		rwpn = &env->world.armory[env->player.inventory.current->current->ref];
		if (env->player.inventory.current->ammo_current)
		{
			env->player.actions.is_shooting = !env->player.actions.is_shooting;
			env->player.actions.mouse_state = rwpn->time_shoot_between;
			Mix_PlayChannel(-1,	rwpn->shot,	0);
			env->player.inventory.current->ammo_current--;
		}
		else
			load_weapon(env);
	}
	if (env->sdl.event.type == SDL_MOUSEBUTTONUP)
		env->player.actions.mouse_state = 0;
	return (0);
}