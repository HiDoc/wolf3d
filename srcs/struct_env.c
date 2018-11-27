/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:20 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/10 14:32:18 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
void	hub_free(t_hub hub)
{
	if (hub.surface != NULL)
		SDL_FreeSurface(hub.surface);
	if (hub.img != NULL)
		SDL_FreeSurface(hub.img);
	if (hub.texture != NULL)
		SDL_DestroyTexture(hub.texture);
}

void	sdl_free(t_sdl sdl)
{
	if (sdl.surface)
		SDL_FreeSurface(sdl.surface);
	if (sdl.texture)
		SDL_DestroyTexture(sdl.texture);
	if (sdl.renderer)
		SDL_DestroyRenderer(sdl.renderer);
	if (sdl.window)
		SDL_DestroyWindow(sdl.window);
}

int		env_free(t_env *env)
{
	int i;

	i = 0;
	while (env->walls[i])
	{
		SDL_FreeSurface(env->walls[i]);
		i++;
	}
	if (env->w_map)
		tab_free(env->w_map, 24);
	if (env->o_map)
		tab_free(env->o_map, 24);
	if (env->enemy)
		SDL_FreeSurface(env->enemy);
	if (env->floor)
		SDL_FreeSurface(env->floor);
	if (env->sky)
		SDL_FreeSurface(env->sky);
	if (env->gun)
		SDL_FreeSurface(env->gun);
	hub_free(env->lscreen);
	hub_free(env->title);
	hub_free(env->life);
	hub_free(env->logo);
	sdl_free(env->sdl);
	free(env);
	return (1);
}

int		fill_obj(t_env *env)
{
	int	x;
	int	y;
	int o_map[24][24]=
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
			{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
			{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
	if (!(env->o_map = (int**)malloc(sizeof(int*) * 24)))
		print_error(1, env);
	y = 0;
	while (y < 24)
	{
		if (!(env->o_map[y] = (int*)malloc(sizeof(int) * 24)))
			print_error(1, env);
		x = 0;
		while (x < 24)
		{
			env->o_map[y][x] = o_map[y][x];
			x++;
		}
		y++;
	}
	return (0);
}
/*
 * Map for wolf, formatted as follow :
 * 0xabcd
 * a : undefined
 * b : undefined
 * c : [wall, floor, object]
 * d : texture number
 */
int		fill_tab(t_env *env)
{
	int	x;
	int	y;
	int w_map[24][24]=
		{
			{0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017 ,0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x012, 0x011, 0x012, 0x013, 0x013, 0x014, 0x014, 0x012, 0x016, 0x017, 0x017, 0x000, 0x017, 0x017, 0x017, 0x017, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x015, 0x000, 0x011, 0x000, 0x011, 0x000, 0x016, 0x000, 0x014, 0x017, 0x000, 0x000, 0x000, 0x017, 0x017, 0x017, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x015, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x015, 0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017, 0x017, 0x017, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x015, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x015, 0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x014, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x014, 0x017, 0x000, 0x000, 0x000, 0x017, 0x017, 0x017, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x013, 0x013, 0x012, 0x015, 0x000, 0x015, 0x012, 0x012, 0x013, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017},
			{0x017, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x000, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x016, 0x016, 0x016, 0x016, 0x016, 0x000, 0x016, 0x016, 0x016, 0x016, 0x000, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x016, 0x017},
			{0x017, 0x014, 0x014, 0x014, 0x014, 0x014, 0x000, 0x014, 0x014, 0x014, 0x016, 0x000, 0x016, 0x012, 0x012, 0x012, 0x012, 0x012, 0x012, 0x012, 0x013, 0x013, 0x013, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x014, 0x016, 0x000, 0x016, 0x012, 0x000, 0x000, 0x000, 0x000, 0x000, 0x012, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x016, 0x012, 0x000, 0x000, 0x015, 0x000, 0x000, 0x012, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x014, 0x016, 0x000, 0x016, 0x012, 0x000, 0x000, 0x000, 0x000, 0x000, 0x012, 0x012, 0x000, 0x012, 0x017},
			{0x017, 0x000, 0x016, 0x000, 0x016, 0x000, 0x000, 0x000, 0x000, 0x014, 0x016, 0x000, 0x000, 0x000, 0x000, 0x000, 0x015, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x015, 0x000, 0x000, 0x000, 0x000, 0x000, 0x014, 0x016, 0x000, 0x016, 0x012, 0x000, 0x000, 0x000, 0x000, 0x000, 0x012, 0x012, 0x000, 0x012, 0x017},
			{0x017, 0x000, 0x016, 0x000, 0x016, 0x000, 0x000, 0x000, 0x000, 0x014, 0x016, 0x000, 0x016, 0x012, 0x000, 0x000, 0x015, 0x000, 0x000, 0x012, 0x000, 0x000, 0x000, 0x017},
			{0x017, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000},
			{0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017, 0x017}
		};
	if (!(env->w_map = (int**)malloc(sizeof(int*) * 24)))
		print_error(1, env);
	y = 0;
	while (y < 24)
	{
		if (!(env->w_map[y] = (int*)malloc(sizeof(int) * 24)))
			print_error(1, env);
		x = 0;
		while (x < 24)
		{
			env->w_map[y][x] = w_map[y][x];
			x++;
		}
		y++;
	}
	fill_obj(env);
	return (0);
}

int		init_env(t_env *env)
{
	env->width = 800;
	env->sdl.surface = NULL;
	env->height = 600;
	env->pos.x = 10;
	env->pos.y = 10;
	env->ang = 2.0;
	env->pang = 0.0;
	env->dir.x = -1.0;
	env->dir.y = 0.0;
	env->plane.x = 0.0;
	env->plane.y = 0.66;
	env->w_map = NULL;
	env->is_updn = 0.0;
	env->portal.out = 0;
	env->portal.in = 0;
	env->logo.ang = 0.0;
	env->hratio = 2;
	env->is_jump = 0;
	img(env);
	fill_tab(env);
	init_thread(env);
	init_sdl(env);
	return (0);
}
