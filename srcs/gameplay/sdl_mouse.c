/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/04/02 00:41:36 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mouse_shoot(t_env *env)
{
	// t_weapon	*rwpn;
	t_actions	*actions;
	// t_wrap_wpn  *current;
	// (void)env;
	actions = &env->player.actions;
	// current = env->player.inventory.current;
	// if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(SDL_BUTTON_LEFT)
	// 	&& current && !env->hud.inventory.is_active
	// 	&& !actions->is_loading && !actions->mouse_state)
	// {
	// 	rwpn = &env->world.armory[current->current->ref];
	// 	if (current->ammo_current)
	// 	{
	// 		actions->is_shooting = !actions->is_shooting;
	// 		actions->mouse_state = rwpn->time_shoot_between;
	// 		// pl_kill_bot(env, mouse, &env->engine.sectors[env->engine.player.sector]);
	// 		// Mix_PlayChannel(0,	rwpn->shot,	0);
	// 		current->ammo_current--;
	// 	}
	// 	else
	// 	{
	// 		load_weapon(env);
	// 		actions->mouse_state = 1;
	// 	}
	// }
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		actions->is_shooting = !actions->is_shooting;
		action_kill(actions->is_shooting, &env->engine.player, &env->player);
		actions->mouse_state = 1;
		printf("shoot\n");
	}
	return (1);
}
