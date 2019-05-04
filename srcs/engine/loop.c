/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:10:00 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 03:08:59 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int				sdl_render(t_env *e)
{
	god_mod(e);
	if (e->menu.status.on)
		draw_menu(e);
	else if (e->hud.inventory.is_active)
	{
		e->player.actions.is_shooting = 0;
		e->player.actions.is_loading = 0;
		print_inventory(e);
		action_inventory(e, 0, 0);
	}
	else
	{
		// si retire alors segv + a laisser avant dfs sinon segv <3
		enemies_frames(e, &e->engine.sectors[e->engine.player.sector]);

		dfs(e);
		handle_gems(e);

		if (!e->god_mod)
			bot_action(e, &e->engine.sectors[e->engine.player.sector]);
		player_bullet(e, &e->player, *e->player.inventory.current->damage);

		handle_doors(e);

		e->hud.is_txt ? ui_draw_msg(e, &e->hud.is_txt, &e->time.tframe) : 0;
		wpn_mouse_wheel(e, e->sdl.event);
		sdl_keyhook_game(e, e->sdl.event, e->sdl.keycodes);
		player_move(&e->engine, &e->engine.player.vision, e->sdl.keycodes);
		handle_sound(e, &e->engine.player.sound);
		ui_put_fps(e, e->time.fps);
		ui_minimap(e);
		handle_weapon(e);

		// si retire alors segv :
		print_hud(e);
	}

	SDL_UpdateTexture(e->sdl.texture, NULL,
		e->sdl.surface->pixels, e->sdl.surface->pitch);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, NULL);
	SDL_RenderPresent(e->sdl.renderer);
	return (1);
}

static int		YourEventFilter(void *userdata, SDL_Event *event)
{
	t_env *env;

	env = (t_env *)userdata;
	if (event->type == SDL_MOUSEBUTTONDOWN
	&& !env->player.actions.mouse_state
	&& env->player.inventory.current->current->ref != RIFLE)
		mouse_shoot(env);
	else if (event->type == SDL_MOUSEBUTTONUP)
		env->player.actions.mouse_state = 0;
	return (1);
}

int				sdl_loop(t_env *env)
{
	env->engine.player.vision.falling = 1;
	env->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	while (!env->finish)
	{
		(!env->menu.status.on)
		? SDL_SetEventFilter(&YourEventFilter, (void *)env) : 0;
		if (env->sdl.keycodes[SDL_SCANCODE_Q]
			|| env->menu.status.quit || env->menu.status.gameover)
			return (0);
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;
			SDL_PollEvent(&env->sdl.event);
			sdl_render(env); // <- lifetime
			if (env->hud.inventory.is_active)
				sdl_keyhook_inventory(env, env->sdl.event, env->sdl.keycodes);
			else if (env->menu.status.on)
				sdl_key_menu(env, env->sdl.event, env->sdl.keycodes);
			else
				(env->player.inventory.current->current->ref == RIFLE)
				? mouse_shoot(env) : 0;
		}
	}
	return (0);
}
