/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:56:11 by abaille           #+#    #+#             */
/*   Updated: 2019/03/14 19:35:59 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	print_wpn_hud(t_env *env, t_wrap_wpn *wpn)
{
	env->player.hud.mix = 1;
	put_img_inv(env, env->player.hud.hud_wpn[wpn->current->ref],
	(t_edge){{W - W / 4.5, H / 1.5}, {W - W / 4.5 + 190, H / 1.5 + 140}},
	(t_edge){{0, 0}, {0, 0}});
	ui_put_string(env, (t_font){GOLD, "", F_NUMB,
	(t_vtx){W - W / 4.5 + 115, H / 1.5 + 80}, 30,
	env->player.inventory.current->ammo_current, -1});
	ui_put_string(env, (t_font){GOLD, "/", F_NUMB,
	(t_vtx){W - W / 4.5 + 130, H / 1.5 + 110}, 30,
	-1, env->player.inventory.current->ammo_magazine});
	return (1);
}

int	print_stack_pad(t_env *env, t_wrap_inv *object, int ref)
{
	char	*tmp;

	if (ref < 5)
	{
		if (!(tmp = ft_itoa(object->nb_stack)))
			return (0);
		if (ref == 0)
			number_font(env, tmp, (t_vctr){W - W / 1.5 + 10, H - H / 4 + 72, 15},
			(SDL_Color){242, 204, 42, 255});
		else if (ref == 1)
			number_font(env, tmp, (t_vctr){W - W / 1.5 + 93, H - H / 4 + 72, 15},
			(SDL_Color){242, 204, 42, 255});
		else
			number_font(env, tmp, (t_vctr){W - W / 1.5 + 53, H - H / 4.5 + 90, 15},
			(SDL_Color){242, 204, 42, 255});
		free(tmp);
		tmp = NULL;
	}
	else if (env->player.actions.is_flying)
		number_font(env, "ON", (t_vctr){W - W / 1.5 + 45, H - H / 4.5 + 10, 20},
		(SDL_Color){242, 204, 42, 255});
	else
		number_font(env, "OFF", (t_vctr){W - W / 1.5 + 45, H - H / 4.5 + 10, 20},
		(SDL_Color){242, 204, 42, 255});
	return (0);
}

int	action_pad(t_env *env, int ref, t_edge limits)
{
	int	i;
	int		rref;

	i = check_object_type(env, ref);
	if (i > -1)
	{
		if (i > 1 && i < 5)
			rref = i - 2;
		else
			rref = ref;
		if (put_img_inv(env, env->world.objects[rref].sprite,
		limits, (t_edge){{0, 0}, {0, 0}})
		&& print_stack_pad(env, &env->player.inventory.objects[i], ref))
			return (1);
		return (0);
	}
	if (ref > 1 && ref < 6)
		ref = ref < 5 ? 3 : 2;
	return (put_img_inv(env, env->player.hud.e_pad[ref],
	limits, (t_edge){{0, 0}, {0, 0}}));
}

int	print_pad(t_env *env)
{
	int	wpad;

	wpad = (W - W / 16) - (W - W / 6);
	action_pad(env, 0, (t_edge){{W - W / 1.5 - 40, H - H / 4 + 60},
	{W - W / 1.5 - 5, H - H / 4 + 90}});
	action_pad(env, 1, (t_edge){{W - W / 1.5 + 110, H - H / 4 + 64},
	{W - W / 1.5 + 140, H - H / 4 + 92}});
	if (env->player.inventory.current)
		action_pad(env, env->player.inventory.current->current->ref + 2,
		(t_edge){{W - W / 1.5 + 40, H - H / 4.5 + 110},
		{W - W / 1.5 + 70, H - H / 4.5 + 140}});
	action_pad(env, 5, (t_edge){{W - W / 1.5 + 37, H - H / 4.5 - 35},
	{W - W / 1.5 + 75, H - H / 4.5}});
	return (0);
}

float	size_bar(int tmax, int datamax, int data)
{
	return ((tmax - tmax / 2.8) / datamax * data + tmax / 2.8);
}

int	draw_img(t_env *env, SDL_Surface *img, t_ixy start, t_edge limit_img)
{
	Uint32	src;
	int		y;
	int		i;
	int		sx;

	sx = start.x;
	while ((start.x < sx + limit_img.v2.x) && sx + limit_img.v2.x < W)
	{
		y = limit_img.v1.y;
		i = start.y;
		while ((i < start.y + limit_img.v2.y) && start.y + limit_img.v2.y < H)
		{
			src = getpixel(img, limit_img.v1.x, y);
			if (src & img->format->Amask)
				setpixel(env->sdl.surface, start.x, i, src);
			i++;
			y++;
		}
		start.x++;
		limit_img.v1.x++;
	}
	return (1);
}

int print_hud(t_env *env)
{
	int	h;
	int	limit_bar;
	int	index;

	h = 200;
	while (h > env->player.health)
		h -= 50;
	// if (env->player.inventory.current)
	// {
	// 	if (!print_wpn_hud(env, env->player.inventory.current))
	// 		return (0);
	// }
	// print_pad(env);
	index = h > 50 ? (int)(h / 50) - 1 : 0;
	draw_img(env, env->player.hud.faces[index], (t_ixy){W / 128, H - H / 2.5},
	(t_edge){{0, 0}, {env->player.hud.faces[index]->w,
	env->player.hud.faces[index]->h}});
	limit_bar = size_bar(env->player.hud.bar[0]->w,
	env->player.max_health, env->player.health);
	draw_img(env, env->player.hud.bar[0], (t_ixy){W / 128, H - H / 2.5},
	(t_edge){{0, 0}, {limit_bar, env->player.hud.bar[0]->h}});
	limit_bar = size_bar(env->player.hud.bar[1]->w,
	env->player.max_shield, env->player.shield);
	draw_img(env, env->player.hud.bar[1], (t_ixy){W / 128, H - H / 2.5},
	(t_edge){{0, 0}, {limit_bar, env->player.hud.bar[1]->h}});
	return (1);
}