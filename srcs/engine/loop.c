/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:10:00 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/30 15:01:02 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int				sdl_render(t_env *env)
{
	god_mod(env);
	if (env->menu.status.on)
		draw_menu(env);
	else if (env->hud.inventory.is_active)
	{
		env->player.actions.is_shooting = 0;
		env->player.actions.is_loading = 0;
		print_inventory(env);
		action_inventory(env, 0, 0);
	}
	else
	{
		// si retire alors segv + a laisser avant dfs sinon segv <3
		enemies_frames(env, &env->engine.sectors[env->engine.player.sector]);

		dfs(env);
		//handle_gems(env);

		if (!env->god_mod)
			bot_action(env, &env->engine.sectors[env->engine.player.sector]);
		player_bullet(env, &env->player, *env->player.inventory.current->damage);


		//if (env->hud.is_txt)
		//	ui_draw_msg(env, &env->hud.is_txt, &env->time.tframe);
		handle_doors(env);
		wpn_mouse_wheel(env, env->sdl.event);
		sdl_keyhook_game(env, env->sdl.event, env->sdl.keycodes);
		player_move(&env->engine, &env->engine.player.vision, env->sdl.keycodes);
		handle_sound(env, &env->engine.player.sound);
		ui_put_fps(env, env->time.fps);
		ui_minimap(env);
		handle_weapon(env);

		// si retire alors segv :
		print_hud(env);
	}

	SDL_UpdateTexture(env->sdl.texture, NULL,
		env->sdl.surface->pixels, env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
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
	while (env->finish == 0)
	{
		(!env->menu.status.on)
		? SDL_SetEventFilter(&YourEventFilter, (void *)env) : 0;
		if (env->sdl.keycodes[SDL_SCANCODE_Q] || env->menu.status.quit)
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
