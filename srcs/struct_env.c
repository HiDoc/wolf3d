/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:20 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 17:01:27 by fmadura          ###   ########.fr       */
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
	0xFF000000, 0xFF0000, 0xFF00, 0xFF);
	return (1);
}

int		init_player(t_env *env)
{
	point_set(&env->player.plane, 0.0, 0.66);
	point_set(&env->player.dir, -1.0, 0.0);
	env->player.inventory.weapons[0] = &env->world.armory[0];
	return (1);
}

int		init_weapon(t_env *env)
{
	env->world.armory[0].ref = 0xa1e0502061A1;
	weapon_set(&env->world.armory[0], "ak47");
	return (1);
}

int		init_env(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(t_env));
	env->sdl.width = WIDTH;
	env->sdl.height = HEIGHT;
	env->player.health = 100;
	env->hratio = 2.0;
	env->minimap.mnp_size = 20;

	return (parse_map(env, filename)
	&& init_player(env)
	&& init_world(env)
	&& init_weapon(env)
	&& init_img(env)
	&& init_surface(env)
	&& init_wobj(env)
	&& put_poster(env)
	&& set_thread(env, 8)
	&& init_sdl(env)
	&& init_menu_surface(env)
	&& load_sounds(env)
	&& launch_screen(env));
}
