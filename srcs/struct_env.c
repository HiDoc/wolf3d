/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:20 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/26 16:07:52 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** Map for wolf, formatted as follow :
** 0xabcd
** a : objects on wall
** b : bullets impact
** c : [wall, floor, object]
** d : texture number
**/

int		init_wobj(t_env *env)
{
	env->wobj.hit = 0;
	env->wobj.poster = 0;
	env->wobj.impact = 0;
	env->wobj.is_bullet = 0;
	env->wobj.simpact =
	SDL_CreateRGBSurface(0, 564, 563, 32,
	0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	return (0);
}

int		init_player(t_env *env)
{
	point_set(&env->player.plane, 0.0, 0.66);
	point_set(&env->player.dir, -1.0, 0.0);
	env->player.inventory.weapons[0] = &env->world.armory[0];
	return (0);
}

int		init_weapon(t_env *env)
{
	env->world.armory[0].ref = 0xa1e0502061A1;
	weapon_set(&env->world.armory[0], "ak47");
	return (0);
}

int		init_env(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(t_env));
	env->sdl.width = WIDTH;
	env->sdl.height = HEIGHT;
	init_weapon(env);
	init_player(env);
	env->player.health = 100;
	env->hratio = 2.0;
	
	env->sdl.surface = SDL_CreateRGBSurface(0, env->sdl.width, env->sdl.height,
	32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	parse_map(env, filename);

	// this is to previsualize the map ------------
	int	i = 0;
	int	j;
	while (i < env->map_h)
	{
		j = 0;
		while (j < env->map_w)
		{
			printf("0x%x ", env->w_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	//exit(EXIT_FAILURE); // to try only the parsing
	// ---------------------------------------------

	// init minimap
	env->minimap.mnp_size = 20;

	img(env);
	init_world(env);
	init_wobj(env);
	put_poster(env);
	init_thread(env, 8);
	init_sdl(env);
	init_menu_surface(env);
	SDL_SetRenderTarget(env->sdl.renderer, env->sdl.texture);
	return (0);
}
