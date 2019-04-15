/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
/*   Updated: 2019/04/16 00:45:39 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	god_mod(t_env *env)
{
	if (env->god_mod)
	{
		env->menu.status.on = 0;
		env->menu.status.home = 0;
		env->menu.status.sound = 0;
		env->player.actions.is_invisible = 1;
	}
	return (1);
}

void	sdl_keymouse_menu(t_env *e, SDL_Event ev, const Uint8 *k)
{
	t_status	*s;

	s = &e->menu.status;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN)
	{
		if (s->home)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			s->main_menu = 1;
			s->home = 0;
		}
		else if (s->main_menu && !s->options_menu && !s->ingame_menu && !s->load_menu)
			action_mainmenu(s, k);
		else if (s->ingame_menu && !s->options_menu)
			action_ingame_menu(s, k);
		else if (s->load_menu)
			action_loadmenu(e, s, k);
		else if (s->options_menu)
			action_optionmenu(e, s, k);
		if (k[SDL_SCANCODE_ESCAPE])
		{
			if (s->options_menu || s->load_menu)
			{
				s->key_change = 0;
				s->options_menu = 0;
				s->load_menu = 0;
			}
			else if (!s->main_menu)
			{
				s->on = !s->on;
				s->ingame_menu = !s->ingame_menu;
				SDL_SetRelativeMouseMode(SDL_TRUE);
				SDL_Delay(300);
			}
			s->current = 0;
		}

	}
}

int	sdl_keyhook_inventory(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_uinv		*ui;
	int			*k;

	ui = &env->hud.inventory;
	k = env->engine.keys;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN)
	{
		if (keycodes[k[I_OINVENTR]])
		{
			ui->is_active = !ui->is_active;
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_Delay(300);
		}
	}
	return (1);
}

void	keyhook_gems(t_env *env, const Uint8 *keycodes)
{
	int	*k;

	k = env->engine.keys;
	if (keycodes[k[I_OJETPACKON]])
		action_gems(env, env->hud.shortcut[0], 0);
	if (keycodes[k[I_OBLUEGEM]])
		action_gems(env, env->hud.shortcut[1], 1);
	if (keycodes[k[I_OGREEGEM]])
		action_gems(env, env->hud.shortcut[2], 2);
	if (keycodes[k[I_OREDGEM]])
		action_gems(env, env->hud.shortcut[3], 3);
	if (keycodes[k[I_OPURPGEM]])
		action_gems(env, env->hud.shortcut[4], 4);
}

int	sdl_keyhook_game(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_engine	*e;
	t_vision	*v;
	int			*k;

	k = env->engine.keys;
	e = &env->engine;
	v = &e->player.vision;
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
	{
		keyhook_gems(env, keycodes);
		if (keycodes[SDL_SCANCODE_O])
			env->god_mod = !env->god_mod;
		if (keycodes[k[I_OPICK]])
			is_pickable_object(env, &env->engine.sectors[e->player.sector]);
		if (k[I_ORELOAD])
			load_weapon(env);
		if (keycodes[k[I_ORELOAD]])
			open_door(env);
		if (keycodes[SDL_SCANCODE_G])
			e->sectors[2].floor = (int)(e->sectors[2].floor + 1) % 41;
		if (keycodes[k[I_OINVENTR]])
		{
			env->hud.inventory.is_active = !env->hud.inventory.is_active;
			SDL_Delay(300);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		if (keycodes[SDL_SCANCODE_ESCAPE])
		{
			env->menu.status.on = !env->menu.status.on;
			env->menu.status.ingame_menu = !env->menu.status.ingame_menu;
			SDL_Delay(300);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}
	return (1);
}
