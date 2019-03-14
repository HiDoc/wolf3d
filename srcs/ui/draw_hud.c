/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:56:11 by abaille           #+#    #+#             */
/*   Updated: 2019/03/12 23:44:19 by abaille          ###   ########.fr       */
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

int	print_health_shield(t_env *env, SDL_Surface *img, t_edge scale_size, t_vtx data)
{
	SDL_Surface		*tmp;
	SDL_Rect	size;
	Uint32		*pxl;
	int			ldrawx;

	size.w = scale_size.v2.x - scale_size.v1.x;
	size.h = scale_size.v2.y - scale_size.v1.y;
	size.x = 0;
	size.y = 0;
	ldrawx = (size.w - size.w / 2.4) / data.x * data.y + size.w / 2.4;
	if (img)
	{
		if (size.w < img->w || size.h < img->h)
		{
			if (!(tmp = SDL_CreateRGBSurface(0, size.w, size.h, 32,
			0xff000000, 0xff0000, 0xff00, 0xff)))
				return (0);
			SDL_LockSurface(tmp);
			pxl = tmp->pixels;
			scale_img(pxl, size, img, (t_ixy){0, 0});
			draw_img(env, (t_edge){{scale_size.v1.x, scale_size.v1.y},
			{ldrawx, scale_size.v2.y}}, tmp, (t_ixy) {0, 0});
			SDL_UnlockSurface(tmp);
			SDL_FreeSurface(tmp);
			tmp = NULL;
		}
		return (1);
	}
	return (0);
}

int print_hud(t_env *env)
{
	int	h;

	h = 200;
	while (h >= env->player.health)
		h -= 50;

	if (env->player.inventory.current)
	{
		if (!print_wpn_hud(env, env->player.inventory.current))
			return (0);
	}
	// print_pad(env);
	return ((put_img_inv(env, env->player.hud.empty_bar, (t_edge){{W / 63, H - H / 3},
	{W / 2.5, H - H / 16}}, (t_edge){{0, 0}, {0, 0}}))
	&& (print_health_shield(env, env->player.hud.bar[0], (t_edge){{W / 63, H - H / 3},
	{W / 2.5, H - H / 16}}, (t_vtx){env->player.max_health, env->player.health}))
	&& (print_health_shield(env, env->player.hud.bar[1], (t_edge){{W / 63, H - H / 3},
	{W / 2.5, H - H / 16}}, (t_vtx){env->player.max_shield, env->player.shield}))
	&& (put_img_inv(env, env->player.hud.faces[h > 50 ? h / 50 : 0], (t_edge){{W / 63, H - H / 3},
	{W / 2.5, H - H / 16}}, (t_edge){{0, 0}, {0, 0}})));
}