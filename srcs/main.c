/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:15 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/19 17:41:26 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int main(int argc, char *argv[])
{
	t_env   *env;

	(void)argv;
	(void)argc;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		print_error(1, NULL);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}
	init_env(env);
	while (1)
	{
		SDL_PollEvent(&env->sdl.event);
		if (env->sdl.event.type == SDL_QUIT)
			break;
		if (env->sdl.event.type == SDL_KEYDOWN)
		{
			sdl_keyhook(env, env->sdl.event);
			copy_sdl(env);
		}
		if (env->sdl.event.type == SDL_MOUSEMOTION)
		{
			int x;
			int y;
			SDL_GetRelativeMouseState(&x, &y);
			if (x || y)
			{
				sdl_motion_mouse(env, x, y);
				copy_sdl(env);
			}
		}
		SDL_SetRenderTarget(env->sdl.renderer, env->sdl.texture);
		SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
		SDL_RenderPresent(env->sdl.renderer);
	}
	SDL_DestroyRenderer(env->sdl.renderer);
	SDL_Quit();
	return 0;
}
