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

int	loop_env(t_env *env)
{
	int x;
	int y;

	while (1)
	{
		SDL_PollEvent(&env->sdl.event);
		if (env->sdl.event.type == SDL_QUIT)
			return (0);
		if (env->sdl.event.type == SDL_KEYDOWN
			|| env->sdl.event.type == SDL_KEYUP
			|| env->sdl.event.type == SDL_MOUSEMOTION)
		{
			if (env->sdl.event.type == SDL_KEYDOWN
				|| env->sdl.event.type == SDL_KEYUP)
				sdl_keyhook(env, env->sdl.event);
			if (env->sdl.event.type == SDL_MOUSEMOTION)
			{
				SDL_GetRelativeMouseState(&x, &y);
				if (x || y)
					sdl_motion_mouse(env, x, y);
			}
			init_thread(env);
			copy_sdl(env);
			SDL_FlushEvent(env->sdl.event.key.keysym.scancode);
			SDL_FreeSurface(env->sdl.surface);
			env->sdl.surface = NULL;
			SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
			SDL_RenderCopy(env->sdl.renderer, env->life.texture, NULL, &env->life.rect);
			SDL_RenderPresent(env->sdl.renderer);
		}
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_env   *env;

	(void)argv;
	(void)argc;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		print_error(1, NULL);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
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
