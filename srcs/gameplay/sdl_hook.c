/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
/*   Updated: 2019/03/11 15:46:35 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			sdl_keyhook(t_env *env, SDL_Event event)
{
	Uint8	keycode;
	const Uint8	*keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	t_character	*p;

	keycode = event.key.keysym.scancode;
	p = &env->player;
	if (event.type == SDL_KEYDOWN)
	{
		if (keycodes[SDL_SCANCODE_C])
			pick_object(env, env->engine.sectors[0].head_object);
		if (keycodes[SDL_SCANCODE_V])
			pick_object(env, env->engine.sectors[0].head_object->next);
		if (keycodes[SDL_SCANCODE_LEFT])
			p->hud.is_txt = give_health(env, p->hud.shortcut[0]);
		if (keycodes[SDL_SCANCODE_RIGHT])
			p->hud.is_txt = give_shield(env, p->hud.shortcut[1]);
		if (keycodes[SDL_SCANCODE_UP])
			p->hud.is_txt = give_jetpack(env, p->hud.shortcut[5]);
		if (keycodes[SDL_SCANCODE_DOWN])
			p->hud.is_txt = give_ammo(env, p->hud.shortcut[p->inventory.current->current->ref + 2]);
		if (keycodes[SDL_SCANCODE_TAB])
			p->inventory.ui.is_active = 1;
		if (keycodes[SDL_SCANCODE_Z])
			p->inventory.ui.is_active = 0;
		if (keycodes[SDL_SCANCODE_R])
			load_weapon(env);
		SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	}
	return (1);
}
