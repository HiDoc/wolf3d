/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
/*   Updated: 2019/03/25 16:51:47 by fmadura          ###   ########.fr       */
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
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_Delay(300);
		}
	}
	return (1);
}

int			sdl_keyhook_game(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_character	*p;
	t_engine	*e;
	t_vision	*v;

	e = &env->engine;
	p = &env->player;
	v = &e->player.vision;
	(void)keycodes;
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
	{

		if (keycodes[SDL_SCANCODE_V])
			pick_object(env, env->engine.sectors[0].head_object->next);
		if (keycodes[SDL_SCANCODE_G])
			e->sectors[2].floor = (int)(e->sectors[2].floor + 1) % 41;
		if (keycodes[SDL_SCANCODE_TAB])
		{
			p->inventory.ui.is_active = !p->inventory.ui.is_active;
			SDL_Delay(300);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}
	return (1);
}
