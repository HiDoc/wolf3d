/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 17:41:45 by fmadura           #+#    #+#             */
/*   Updated: 2018/12/27 19:14:24 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					render_env(t_env *env)
{
	SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP | SDL_MOUSEMOTION);
	SDL_FreeSurface(env->sdl.surface);
	SDL_RenderClear(env->sdl.renderer);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderCopy(env->sdl.renderer, env->life.texture, NULL, &env->life.rect);
	SDL_RenderPresent(env->sdl.renderer);
	return (0);
}

static void inline	loop_weapons(t_env *env, int *frame)
{
	if (env->is_shootin)
	{
		shoot_weapon(env, *frame);
		++(*frame);
	}
	else if (env->ld_wp)
	{
		put_gun_load(env, *frame);
		++(*frame);
	}
	else
	{
		put_gun(env);
		*frame = 0;
	}
	if (env->is_jump)
		player_jump(env);
}

void				loop_env(t_env *env)
{
	int		frame;
	int		fps;
	Uint32	time_a;
	int		mx;
	int		my;

	time_a = 0;
	fps = 0;
	while (1)
	{
		SDL_PollEvent(&env->sdl.event);
		SDL_GetRelativeMouseState(&mx, &my);
		if (env->sdl.event.type == SDL_QUIT)
			break;
		sdl_keyhook(env, env->sdl.event);
		if (mx || my)
			sdl_motion_mouse(env, mx, my);
		init_thread(env, 8);
		loop_weapons(env, &frame);
		struct_minimap(env);
		ui_put_fps(env, fps);
		copy_sdl(env);
		health(env);
		render_env(env);
		time_a = SDL_GetTicks();
	}
}

int					main(int argc, char *argv[])
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
	env->minimap.mnp_size = 20; // a mettre la ou il faut
	load_sounds(env);
	launch_screen(env);
	loop_env(env);
	env_free(env);
	return (0);
}
