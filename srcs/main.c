/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 17:41:45 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/03 18:27:09 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	render_env(t_env *env)
{
	SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP | SDL_MOUSEMOTION);
	SDL_FreeSurface(env->sdl.surface);
	SDL_RenderClear(env->sdl.renderer);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderCopy(env->sdl.renderer, env->life.texture, NULL, &env->life.rect);
	SDL_RenderPresent(env->sdl.renderer);
	return (0);
}

int	loop_env(t_env *env)
{
	int		x;
	int		y;
	int		frame;
	Uint32	time_a;
	Uint32	time_b;

	time_a = 0;
	time_b = 0;
	frame = 0;
	while (1)
	{
		SDL_PollEvent(&env->sdl.event);
		if (env->sdl.event.type == SDL_QUIT)
			return (0);
		time_b = SDL_GetTicks();
		if (time_b - time_a > SCREEN_TIC)
		{
			sdl_keyhook(env, env->sdl.event);
			SDL_GetRelativeMouseState(&x, &y);
			if (x || y)
				sdl_motion_mouse(env, x, y);
			if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
			{
				if (env->wobj.impact < 6)
					env->wobj.impact++;
				env->mouse.x = x;
				env->mouse.y = y;
				sdl_mouse_click(env, x, y);
			}
			init_thread(env);
			if (env->is_shootin)
			{
				shoot_weapon(env, frame);
				frame++;
			}
			else if (env->ld_wp)
			{
				put_gun_load(env, frame);
				frame++;
			}
			else
			{
				put_gun(env);
				frame = 0;
			}
			if (env->is_jump)
			{
				player_jump(env);
			}
			copy_sdl(env);
			render_env(env);
			time_a = SDL_GetTicks();
		}
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_env *env;

	(void)argv;
	(void)argc;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (1);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		"Couldn't initialize SDL: %s", SDL_GetError());
		return (3);
	}
	if (TTF_Init() < 0)
	{
		fprintf(stderr, "init TTF failed: %s\n", SDL_GetError());
		exit(1);
	}
	init_env(env);
	load_sounds(env);
	launch_screen(env);
	loop_env(env);
	Mix_FreeChunk(env->sounds.shot);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	env_free(env);
	return (0);
}
