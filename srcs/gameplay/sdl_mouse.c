/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/27 19:42:41 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	mouse_shoot(t_env *env)
{
	t_weapon	*rwpn;
	// t_actions	*actions;

	// actions = &env->player.actions;
	printf("\nlogic\n");
	printf("%p\n", &env->player.inventory.current);
	printf("%d\n", env->hud.inventory.is_active);
	printf("%d\n", env->player.actions.is_loading);
	printf("%d\n", env->player.actions.mouse_state);
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)
	&& env->player.inventory.current
	&& !env->hud.inventory.is_active
	&& !env->player.actions.is_loading
	&& !env->player.actions.mouse_state)
	{
		rwpn = &env->world.armory[env->player.inventory.current->current->ref];
		if (env->player.inventory.current->ammo_current)
		{
			env->player.actions.is_shooting = !env->player.actions.is_shooting;
			env->player.actions.mouse_state = rwpn->time_shoot_between;
			printf("%f \n", rwpn->time_shoot_between);
			// Mix_PlayChannel(0,	rwpn->shot,	0);
			env->player.inventory.current->ammo_current--;
		}
		else
		{
			load_weapon(env);
			env->player.actions.mouse_state = 1;
		}
	}
	return (0);
}
