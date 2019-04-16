/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:57 by abaille           #+#    #+#             */
/*   Updated: 2019/04/11 10:14:13 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int    ui_put_fps(t_env *env, int fps)
{
	ui_put_data(env, (t_font){RED, "fps : ", env->hud.text.number, (t_vtx){10, 10}, W / 40, -1, fps});
    return (1);
}

int		draw_pick_infos(t_env *env, t_wrap_sect *obj, int ref)
{
	t_bloc	fill;
	SDL_Rect	rect;

	rect = (SDL_Rect){W / 2, H / 2, env->hud.text.pick->w, env->hud.text.pick->h};
	fill = (t_bloc){{{0, 0, 0, 0}, NULL}, {{0, 0, 0, 0}, NULL}, NULL, NULL, NULL,
	rect, {{0, 0}, {0, 0}}};
	if (obj->is_pickable)
	{
		draw_img(env, env->hud.text.pick, &fill);
		fill.rect.x += env->hud.text.pick->w;
		draw_img(env, env->hud.text.obj_names[ref], &fill);
	}
	return (1);
}

int		print_description_object(t_env *env, int i, int j)
{
	int			x;
	int			y;
	t_bloc		fill;
	SDL_Rect	rect;

	SDL_GetMouseState(&x, &y);
	if ((i = select_object(env->player.inventory.objects, (t_ixy){x, y},
	env->hud.inventory.objects, 6)) > -1)
		env->hud.txt_inv = env->player.inventory.objects[i].current->ref;
	else if ((j = select_object(env->player.inventory.gems, (t_ixy){x, y},
	env->hud.inventory.gems, 4)) > -1)
		env->hud.txt_inv = env->player.inventory.gems[j].current->ref;
	else
		return (1);
	rect = (SDL_Rect){i > -1 ? W / 40 : W / 10, i > -1 ? H / 7.05 : H / 2.1,
	env->hud.text.i_obj_description[env->hud.txt_inv]->w,
	env->hud.text.i_obj_description[env->hud.txt_inv]->h};
	fill = (t_bloc){{{0, 0, 0, 0}, NULL}, {{0, 0, 0, 0}, NULL},
	NULL, NULL, NULL, rect, {{0, 0}, {0, 0}}};
	draw_img(env, env->hud.text.i_obj_description[env->hud.txt_inv], &fill);
	return (1);
}

static void		print_stats(t_env *env, int i)
{
	t_vtx		p;
	const char *str[NB_STATS] = {D_LEVEL, D_SECTOR, D_KTOGO,
	D_KILLS, D_DEATHS, D_TIMEPLAY, D_KD_RATIO, D_KD_PERMN,
	D_K_MAGNUM, D_K_SHOTGUN, D_K_RIFLE, D_K_RPG, D_K_FIST};
	const t_vtx	pos[3] = {{W - (W / 3), H / 50}, {W - W / 3.3, H / 7},
	{W - W / 3.4, H / 4.9}};
	const float	size[4] = {W / 23, W / 30, W / 40, W / 60};
	float		div_y;

	while (++i < NB_STATS)
	{
		i < I_KILLS ? p = pos[i] : (t_vtx){0, 0};
		if (i > I_KTOGO)
		{
			p.x = i < I_K_MAGNUM ? W - W / 1.9 : W - W / 3.0;
			div_y = (i == I_KILLS || i == I_K_MAGNUM) ? 1.25 : div_y - .05;
			p.y = H / div_y;
		}
		ui_put_data(env, (t_font){WHITE, str[i], i == 0
		? env->hud.text.doom : env->hud.text.text, p,
		i < I_KILLS ? size[i] : size[I_KILLS], -1, env->stats.data[i]});
	}
}

int     ui_txt_inv(t_env *env)
{
	const t_vtx	pos[4] = {
		{W / 40, H / 50}, {W / 40, H / 1.6},
		{W / 40, H / 2.15}, {W / 2.2, H / 1.4}};
	t_bloc		fill;
	SDL_Rect	rect;
	int			i;
	int			r;

	i = -1;
	r = T_INVENTORY;
	while (++i < 4)
	{
		rect = (SDL_Rect){pos[i].x, pos[i].y,
		env->hud.text.string[r]->w, env->hud.text.string[r]->h};
		fill = (t_bloc){
		{{0, 0, 0, 0}, NULL}, {{0, 0, 0, 0}, NULL}, NULL, NULL, NULL,
		rect, {{0, 0}, {0, 0}}};
		draw_img(env, env->hud.text.string[r++], &fill);
	}
	print_stats(env, -1);
    return (print_description_object(env, -1, -1));
}

int		ui_icon_data(t_env *env, t_vtx v, int iter)
{
	int				data;
	SDL_Color 		c;
	const SDL_Color	clrs[4] = {
		{8, 255, 8, 255}, {42, 204, 242, 255},
		{242, 204, 42, 255}, {255, 0, 0, 255}};

	if (iter == 0)
	{
		data = env->player.health;
		c = clrs[0];
	}
	else
	{
		data = env->player.shield;
		c = data < 200 ? clrs[1] : clrs[2];
	}
	if (data < 100)
		c = clrs[3];
	ui_put_data(env, (t_font){c, "%", env->hud.text.text,
	(t_vtx){v.x, v.y}, W / 45, data, -1});
	return (1);
}

int	ui_draw_msg(t_env *env, int *nb, int *tframe)
{
	t_bloc	fill;
	SDL_Rect	rect;

	if (*nb && env->hud.text.string[*nb])
	{
		rect = (SDL_Rect){W / 128, H - H / 2.5, env->hud.text.string[*nb]->w, env->hud.text.string[*nb]->h};
		fill = (t_bloc){{{0, 0, 0, 0}, NULL}, {{0, 0, 0, 0}, NULL}, NULL, NULL, NULL,
		rect, {{0, 0}, {0, 0}}};
		draw_img(env, env->hud.text.string[*nb], &fill);
		if (*tframe < 60)
			++(*tframe);
		else
		{
			*tframe = 0;
			*nb = 0;
		}
	}
	return (0);
}
