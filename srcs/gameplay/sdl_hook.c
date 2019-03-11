/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/11 16:00:28 by fmadura          ###   ########.fr       */
=======
/*   Updated: 2019/03/11 15:46:35 by abaille          ###   ########.fr       */
>>>>>>> 5104a8df38ba76e89daf6cab944b41b5acecd0c5
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			sdl_keyhook_inventory(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_uinv		*ui;

	ui = &env->player.inventory.ui;
	if (ev.type == SDL_KEYDOWN)
	{
		if (keycodes[SDL_SCANCODE_TAB])
			ui->is_active = !ui->is_active;
		SDL_FlushEvent(SDL_KEYDOWN);
	}
	return (1);
}

int			sdl_keyhook_game(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_character	*p;

	p = &env->player;
	if (ev.type == SDL_KEYDOWN)
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
		{
			p->inventory.ui.is_active = !p->inventory.ui.is_active;
			SDL_Delay(300);
		}
		if (keycodes[SDL_SCANCODE_R])
			load_weapon(env);
		SDL_FlushEvent(SDL_KEYDOWN);
	}
	return (1);
}
