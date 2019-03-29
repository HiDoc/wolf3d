/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/28 16:58:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_floor(t_env *env)
{
	env->world.surfaces.floors[0].sprite = new_surface("floor/01");
	env->world.enemies[0].sprite = new_surface("enemies/enemy");
}

int		init_gameplay_env(t_env *env)
{
	return (init_fonts(&env->hud.text)
	&& init_consumable(env)
	&& init_character(&env->player)
	&& set_simple_strings(env, 0, 0)
	&& init_hud_container(env)
	&& init_weapon(env));
}

int		main(void)
{
	t_env			env;

	ft_bzero(&env, sizeof(t_env));
	initialisation(&env);
	ft_bzero(&env.engine, sizeof(t_engine));

	load_tilesets(&env);
	LoadData(&env.engine, &env);
	if (!init_gameplay_env(&env))
	{
		UnloadData(env.sdl.texture, env.sdl.renderer, env.sdl.window, &env.engine);
		free_ui(&env);
		return (0);
	}
	verify_map(&env.engine);
	init_floor(&env);
	init_skybox(&env);

	init_container(&env);
	if (!(init_minimap(&env)))
	{
		// quitter sdl, ttf ,free, etc...
		return (0);
	}
	sdl_loop(&env);
	UnloadData(env.sdl.texture, env.sdl.renderer, env.sdl.window, &env.engine);
	free_ui(&env);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	return (0);
}
