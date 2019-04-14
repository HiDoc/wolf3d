/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
/*   Updated: 2019/04/14 01:05:25 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	god_mod(t_env *env)
{
	if (env->god_mod)
	{
		env->player.actions.is_invisible = 1;
		env->player.actions.is_invulnerable = 1;
	}
	else
	{
		env->player.actions.is_invisible = 0;
		env->player.actions.is_invulnerable = 0;
	}

	return (1);
}

void	scroll_menu(int *cur, const Uint8 *k, int start, int limit)
{
	*cur += k[SDL_SCANCODE_DOWN] ? 1 : -1;
	*cur < start ? *cur = limit - 1 : 0;
	*cur == limit ? *cur = start : 0;
}

void	sdl_keyhook_menu(t_env *e, SDL_Event ev, const Uint8 *k)
{
	t_status	*s;

	s = &e->menu.status;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN)
	{
		if (s->home && k[SDL_SCANCODE_RETURN])
		{
			s->main_menu = 1;
			s->home = 0;
		}
		else if (s->main_menu)
		{
			scroll_menu(&s->current, k, 0, NB_BLOC_NG);
			if (k[SDL_SCANCODE_RETURN])
			{
				s->current == 0 ? s->on = 0 : 0; //launch cinematik ? s->on = 0; // provisoire
				s->current == 1 ? s->load_menu = 1 : 0;
				s->current == 2 ? s->options_menu = 1 : 0;
				s->current == 3 ? s->quit = 1 : 0;
				s->main_menu = 0;
				s->current = 0;
			}

		}
		else if (s->ingame_menu)
		{
			s->current < 2 ? s->current = 2 : s->current;
			scroll_menu(&s->current, k, 2, NB_BLOC_IG);
			if (k[SDL_SCANCODE_LEFT] && s->current == 3)
				s->current = 2;
			else if (k[SDL_SCANCODE_RIGHT] && s->current == 2)
				s->current = 3;
			else if (k[SDL_SCANCODE_RETURN])
			{
				if (s->current == 2)
				{
					s->on = !s->on;
					s->current = 3;
				}
				else if (s->current == 3)
					s->nb_save++; //	save game
				else if (s->current == 4)
				s->current == 4 ? s->options_menu = 1 : 0;
				s->current == 5 ? s->main_menu = 1 : 0;
				s->ingame_menu = 0;
				s->current = 0;
			}
		}
		// if (s->load_menu)
		// {
		// 	if ()
		// }
		else if (s->options_menu)
		{
			s->current < 4 ? s->current = 4 : 0;
			scroll_menu(&s->current, k, 4, NB_OPT_MENU);
			if (k[SDL_SCANCODE_LEFT] && s->current == 4)
				s->current = 3;
			else if (k[SDL_SCANCODE_RIGHT] && s->current == 3)
				s->current = 4;
			else if (k[SDL_SCANCODE_RETURN])
			{
				if (s->current == 4)
					s->on = 0;
				else if (s->current == 1)
					s->nb_save++; //	save game
				else if (s->current == 2)
					s->options_menu = 1;
				else if (s->current == 3)
					s->main_menu = 1;
				s->options_menu = 0;
				s->current = 0;
			}
		}
		if (k[SDL_SCANCODE_ESCAPE] && !s->home && !s->main_menu)
		{
			s->on = !s->on;
			if (s->load_menu)
				s->load_menu = 0;
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_Delay(300);
		}

	}
}

int	sdl_keyhook_inventory(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_uinv		*ui;
	int			*k;

	ui = &env->hud.inventory;
	k = env->menu.keys;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN)
	{
		if (keycodes[SDL_GetScancodeFromKey(k[I_OINVENTR])])
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

	k = env->menu.keys;
	if (keycodes[SDL_GetScancodeFromKey(k[I_OJETPACKON])])
		action_gems(env, env->hud.shortcut[0], 0);
	if (keycodes[SDL_GetScancodeFromKey(k[I_OBLUEGEM])])
		action_gems(env, env->hud.shortcut[1], 1);
	if (keycodes[SDL_GetScancodeFromKey(k[I_OGREEGEM])])
		action_gems(env, env->hud.shortcut[2], 2);
	if (keycodes[SDL_GetScancodeFromKey(k[I_OREDGEM])])
		action_gems(env, env->hud.shortcut[3], 3);
	if (keycodes[SDL_GetScancodeFromKey(k[I_OPURPGEM])])
		action_gems(env, env->hud.shortcut[4], 4);
}

int	sdl_keyhook_game(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_engine	*e;
	t_vision	*v;
	int			*k;

	k = env->menu.keys;
	e = &env->engine;
	v = &e->player.vision;
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
	{
		keyhook_gems(env, keycodes);
		if (keycodes[SDL_SCANCODE_O])
			env->god_mod = !env->god_mod;
		if (keycodes[SDL_GetScancodeFromKey(k[I_OPICK])])
			is_pickable_object(env, &env->engine.sectors[e->player.sector]);
		if (keycodes[SDL_SCANCODE_R])
			load_weapon(env);
		if (keycodes[SDL_GetScancodeFromKey(k[I_OOPENDOOR])])
			open_door(env);
		if (keycodes[SDL_SCANCODE_G])
			e->sectors[2].floor = (int)(e->sectors[2].floor + 1) % 41;
		if (keycodes[SDL_GetScancodeFromKey(k[I_OINVENTR])])
		{
			env->hud.inventory.is_active = !env->hud.inventory.is_active;
			SDL_Delay(300);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		if (keycodes[SDL_SCANCODE_ESCAPE])
		{
			env->menu.status.on = !env->menu.status.on;
			env->menu.status.ingame_menu = 1;
			SDL_Delay(300);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}
	return (1);
}
