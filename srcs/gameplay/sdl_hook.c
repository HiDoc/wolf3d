/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
/*   Updated: 2019/04/04 13:29:38 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	sdl_keyhook_inventory(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_uinv		*ui;

	ui = &env->hud.inventory;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN)
	{
		if (keycodes[SDL_SCANCODE_TAB])
		{
			ui->is_active = !ui->is_active;
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_Delay(300);
		}
	}
	return (1);
}

int	keyhook_gems(t_env *env, const Uint8 *keycodes)
{

	if (keycodes[SDL_SCANCODE_1])
		action_gems(env, env->hud.shortcut[0], 0);
	if (keycodes[SDL_SCANCODE_2])
		action_gems(env, env->hud.shortcut[1], 1);
	if (keycodes[SDL_SCANCODE_3])
		action_gems(env, env->hud.shortcut[2], 2);
	if (keycodes[SDL_SCANCODE_4])
		action_gems(env, env->hud.shortcut[3], 3);
	if (keycodes[SDL_SCANCODE_5])
		action_gems(env, env->hud.shortcut[4], 4);
	return (1);
}

int	sdl_keyhook_game(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_engine	*e;
	t_vision	*v;

	e = &env->engine;
	v = &e->player.vision;
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
	{
		keyhook_gems(env, keycodes);
		if (keycodes[SDL_SCANCODE_E])
			is_pickable_object(env, &env->engine.sectors[e->player.sector]);
		if (keycodes[SDL_SCANCODE_R])
			load_weapon(env);
		if (keycodes[SDL_SCANCODE_G])
			e->sectors[2].floor = (int)(e->sectors[2].floor + 1) % 41;
		if (keycodes[SDL_SCANCODE_TAB])
		{
			env->hud.inventory.is_active = !env->hud.inventory.is_active;
			SDL_Delay(300);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}
	return (1);
}
