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
	SDL_SetRenderTarget(env->sdl.renderer, env->sdl.texture);
	launch_screen(env);
//	turn_logo(env);
	while (1)
	{
		int i = 0;
		SDL_PollEvent(&env->sdl.event);
		if (env->sdl.event.type == SDL_QUIT)
			break;
		if (env->sdl.event.type == SDL_KEYDOWN)
		{
			sdl_keyhook(env, env->sdl.event);
			copy_sdl(env);
			i++;
		}
		if (env->sdl.event.type == SDL_KEYUP)
		{
			sdl_keyhook(env, env->sdl.event);
			copy_sdl(env);
			i++;
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
			i++;
		}
		if (env->sdl.event.type == SDL_MOUSEBUTTONDOWN)
		{
			int x;
			int y;
			if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
			{
				if (x || y)
				{
					if (env->wobj.impact < 6)
						env->wobj.impact++;
					env->mouse.x = x;
					env->mouse.y = y;
					sdl_mouse_click(env, x, y);
					copy_sdl(env);
				}
			}
			i++;
		}
		// if (env->sdl.event.type == SDL_MOUSEBUTTONUP)
		// {
		// 	int x;
		// 	int y;
		// 	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
		// 	{
		// 		if (x || y)
		// 		{
		// 			sdl_mouse_click(env, x, y);
		// 			copy_sdl(env);
		// 		}
		// 	}
		// 	i++;
		// }
		if (i)
		{	
			//SDL_SetTextureColorMod(env->sdl.texture, 255, 255, 255);
			SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
			SDL_RenderCopy(env->sdl.renderer, env->life.texture, NULL, &env->life.rect);
			SDL_RenderPresent(env->sdl.renderer);
			// SDL_FlushEvent(env->sdl.event.key.keysym.scancode);
			SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
			SDL_FlushEvent(env->sdl.event.button.type);
		}
	}
	Mix_FreeChunk(env->sounds.shot);
	Mix_CloseAudio();
	SDL_DestroyRenderer(env->sdl.renderer);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
