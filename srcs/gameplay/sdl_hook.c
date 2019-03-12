/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
/*   Updated: 2019/03/11 18:15:17 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			sdl_keyhook_inventory(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_uinv		*ui;

	ui = &env->player.inventory.ui;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN)
	{
		if (keycodes[SDL_SCANCODE_TAB])
		{
			ui->is_active = !ui->is_active;
			SDL_WarpMouseInWindow(env->sdl.window, W/2, H/2);
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_Delay(300);
		}
		SDL_FlushEvent(SDL_KEYDOWN);
	}
	return (1);
}

int			sdl_keyhook_game(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_character	*p;
	t_vision	*v;

	p = &env->player;
	v = &env->engine.player.vision;
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
	{
		if (keycodes[SDL_SCANCODE_SPACE])
		{
			// add flying here
			if (v->ground)
			{
				env->engine.player.velocity.z += 0.5;
				v->falling = 1;
			}

		}
		v->ducking = (keycodes[SDL_SCANCODE_LCTRL] || keycodes[SDL_SCANCODE_RCTRL]);
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
		{
			p->inventory.ui.is_active = !p->inventory.ui.is_active;
			SDL_Delay(300);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		if (keycodes[SDL_SCANCODE_R])
			load_weapon(env);
		SDL_FlushEvent(SDL_KEYDOWN);
	}
	return (1);
}
