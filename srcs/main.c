/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/22 17:06:08 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int				sdl_mainmenu_render(t_env *env)
{
	draw_menu(env);
	SDL_UpdateTexture(env->sdl.texture, NULL,
		env->sdl.surface->pixels, env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
	return (1);
}

static void				mainmenu_loop(t_env *env)
{
	/* menu_loop */
	env->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	while (env->menu.status.on)
	{
		if (env->sdl.keycodes[SDL_SCANCODE_Q] || env->menu.status.quit)
			doom_exit();
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;

			SDL_PollEvent(&env->sdl.event);
			
			sdl_mainmenu_render(env);
			sdl_key_menu(env, env->sdl.event, env->sdl.keycodes);
		}
	}
}

int		main(int ac, char **av)
{
	t_env	env;

	/* init env */
	init_env(ac, av, &env);
	set_msc_menu(&env, &env.menu.status);

	/* parse world names */
	load_worlds(&env);
	
	/* mainmenu loop */
	mainmenu_loop(&env);

	/* world loop */
	int iprovisoire = 0;
	while (/**env.level*/iprovisoire < 5)
	{
		env.finish = 0;	

		// display text start

		/* load level */
		load_map(&env.engine, &env);
		init_minimap(&env);

		/* gameloop */
		sdl_loop(&env);

		// display text end

		/* free level */
		//free_map();
		lt_release(env.engine.minimap.surface);
		lt_release(env.engine.minimap.background);

		/*(env.level)++;*/
		iprovisoire++;
	}

	/* free and exit */
	doom_exit();
	return (0);
}
