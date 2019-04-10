/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/04/10 15:01:42 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mouse_shoot(t_env *env)
{
	t_weapon	*rwpn;
	t_actions	*actions;
	t_wrap_wpn  *current;

	(void)env;
	actions = &env->player.actions;
	current = env->player.inventory.current;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& current && !env->hud.inventory.is_active && !actions->is_loading
		&& !actions->mouse_state)
	{
		rwpn = &env->world.armory[current->current->ref];
		if (*current->ammo_current || current->current->ref == FIST)
		{
			actions->is_shooting = !actions->is_shooting;
			pl_new_kill(env, &env->engine.player, &env->player);
			actions->mouse_state = rwpn->time_shoot_between;
			// Mix_PlayChannel(0,	rwpn->shot,	0);
			current->current->ref != FIST ? *current->ammo_current -= 1 : 0;
			current->current->ref == RPG ? load_weapon(env) : 0;
		}
		else
		{
			load_weapon(env);
			actions->mouse_state = 1;
		}
	}
	return (1);
}
