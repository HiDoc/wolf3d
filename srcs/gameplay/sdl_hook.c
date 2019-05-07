/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:52 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 19:20:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	sdl_keyhook_menu(t_env *e, SDL_Event ev, const Uint8 *k)
{
	t_status	*s;

	s = &e->menu.status;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN)
	{
		if (s->home)
		{
			s->main_menu = 1;
			s->home = 0;
		}
		else if (s->main_menu && !s->options_menu
				&& !s->ingame && !s->load_menu && !s->new_game)
			action_mainmenu(e, s, k);
		else if (s->ingame && !s->options_menu)
			action_ingame_menu(e, s, k);
		else if (s->load_menu)
			action_loadmenu(e, s, k);
		else if (s->options_menu)
			action_optionmenu(e, s, k);
		else if (s->new_game)
			action_newgame_menu(e, s, k);
		if (k[SDL_SCANCODE_ESCAPE])
			access_menu(e, s, 0);
	}
}

int	sdl_keyhook_inventory(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_uinv	*ui;
	int		*k;

	ui = &env->hud.inventory;
	k = env->engine.keys;
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN)
	{
		if (keycodes[k[I_OINVENTR]])
		{
			ui->is_active = !ui->is_active;
			if ((SDL_SetRelativeMouseMode(SDL_TRUE)) < 0)
				doom_error_exit("Doom_nukem error on SDL_SetRelativeMouseMode");
			SDL_Delay(300);
		}
	}
	return (1);
}

void	sdl_keyhook_gems(t_env *env, const Uint8 *keycodes)
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

int		sdl_keyhook_game(t_env *env, SDL_Event ev, const Uint8 *keycodes)
{
	t_engine	*e;
	t_vision	*v;
	int			*k;

	k = env->engine.keys;
	e = &env->engine;
	v = &e->player.vision;
	if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
	{
		sdl_keyhook_gems(env, keycodes);
		if (keycodes[SDL_SCANCODE_N] && env->god_mod)
			env->finish = 1;
		if (keycodes[SDL_SCANCODE_O])
			env->god_mod = !env->god_mod;
		if (keycodes[k[I_OPICKOPN]])
			access_object(env, &env->engine.sectors[e->player.sector]);
		if (keycodes[k[I_ORELOAD]])
			load_weapon(env);
		if (keycodes[k[I_OPICKOPN]])
			access_door(env);
		if (keycodes[k[I_OINVENTR]])
			access_inventory(env);
		if (keycodes[SDL_SCANCODE_ESCAPE])
			access_menu(env, &env->menu.status, 1);
	}
	return (1);
}
