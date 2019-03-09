/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:56:11 by abaille           #+#    #+#             */
/*   Updated: 2019/03/09 23:27:28 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	print_wpn_hud(t_env *env, t_weapon *wpn)
{
	char	*tmp;

	put_img_inv(env, env->player.hud.hud_wpn[wpn->type - 2],
	(t_edge){{W - W / 4.5, H / 1.5}, {W - W / 4.5 + 190, H / 1.5 + 140}},
	(t_edge){{0, 0}, {0, 0}});
	if (!(tmp = ft_itoa(env->player.inventory.current->ammo_current)))
		return (0);
	number_font(env, tmp, (t_vctr){W - W / 4.5 + 115, H / 1.5 + 80, 30},
	(SDL_Color){242, 204, 42, 255});
	free(tmp);
	tmp = NULL;
	if (!(tmp = ft_strrjoin("/",
	ft_itoa(env->player.inventory.current->ammo_magazine))))
		return (0);
	number_font(env, tmp, (t_vctr){W - W / 4.5 + 130, H / 1.5 + 110, 30},
	(SDL_Color){242, 204, 42, 255});
	free(tmp);
	tmp = NULL;
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
		put_img_inv(env, env->world.objects[rref].sprite,
		limits, (t_edge){{0, 0}, {0, 0}});
		print_stack_pad(env, &env->player.inventory.objects[i], ref);
		return (1);
	}
	if (ref > 1 && ref < 6)
		ref = ref < 5 ? 3 : 2;
	put_img_inv(env, env->player.hud.e_pad[ref],
	limits, (t_edge){{0, 0}, {0, 0}});
	return (1);
}

int	print_pad(t_env *env)
{
	int	wpad;

	wpad = (W - W / 16) - (W - W / 6);
	put_img_inv(env, env->player.hud.pad,
	(t_edge){{W - W / 1.5, H - H / 4.5}, {W - W / 1.5 + 110, H - H / 4.5 + 110}},
	(t_edge){{0, 0}, {0, 0}});
	action_pad(env, 0, (t_edge){{W - W / 1.5 - 40, H - H / 4 + 60},
	{W - W / 1.5 - 5, H - H / 4 + 90}});
	action_pad(env, 1, (t_edge){{W - W / 1.5 + 110, H - H / 4 + 64},
	{W - W / 1.5 + 140, H - H / 4 + 92}});
	if (env->player.inventory.current)
		action_pad(env, env->player.inventory.current->type,
		(t_edge){{W - W / 1.5 + 40, H - H / 4.5 + 110},
		{W - W / 1.5 + 70, H - H / 4.5 + 140}});
	action_pad(env, 5, (t_edge){{W - W / 1.5 + 37, H - H / 4.5 - 35},
	{W - W / 1.5 + 75, H - H / 4.5}});
	return (0);
}

int print_hud(t_env *env)
{
	put_img_inv(env, env->player.inventory.ui.icon[0],
	(t_edge){{40, H - 75}, {70, H - 45}}, (t_edge){{0, 0}, {0, 0}});
	put_img_inv(env, env->player.inventory.ui.icon[1],
	(t_edge){{40, H - 115}, {70, H - 85}}, (t_edge){{0, 0}, {0, 0}});
	draw_img(env, (t_edge){{80, H - 80 - env->player.hud.empty_bar->h},
	{80 + env->player.hud.empty_bar->w, H - 80}}, env->player.hud.empty_bar, (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 80 - env->player.hud.bar[1]->h},
	{80 + env->player.shield, H - 80}}, env->player.hud.bar[1], (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 40 - env->player.hud.empty_bar->h},
	{80 + env->player.hud.empty_bar->w, H - 40}}, env->player.hud.empty_bar, (t_ixy){0, 0});
	draw_img(env, (t_edge){{80, H - 40 - env->player.hud.bar[0]->h},
	{80 + env->player.health, H - 40}}, env->player.hud.bar[0], (t_ixy){0, 0});
	if (env->player.inventory.current)
		print_wpn_hud(env, env->player.inventory.current);
	print_pad(env);
	return (0);
}