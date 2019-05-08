/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 12:49:11 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	pl_is_shooting(t_env *e, t_wrap_wpn *current, t_actions *actions)
{
	return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& current && !e->hud.inventory.is_active && !actions->is_loading
		&& !actions->mouse_state && !e->menu.status.on);
}

void		mouse_shoot(t_env *env)
{
	t_weapon	*rwpn;
	t_actions	*actions;
	t_wrap_wpn	*current;

	actions = &env->player.actions;
	current = env->player.inventory.current;
	if (pl_is_shooting(env, current, actions))
	{
		rwpn = &env->world.armory[current->ref];
		if (*current->ammo_current || current->ref == FIST)
		{
			actions->is_shooting = !actions->is_shooting;
			pl_new_kill(env, &env->engine.player, &env->player);
			actions->mouse_state = rwpn->time_shoot_between;
			play_chunk(-1, env->sound.shot[current->ref], 0);
			(current->ref != FIST) ? *current->ammo_current -= 1 : 0;
			(current->ref == RPG) ? load_weapon(env) : 0;
		}
		else
		{
			load_weapon(env);
			actions->mouse_state = 1;
		}
	}
}
