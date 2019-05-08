/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:57 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 17:09:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		draw_pick_infos(t_env *env, t_wrap_sect *obj, int ref)
{
	const char	*tab[WORLD_NB_OBJECTS] = {N_HEALTH, N_SHIELD, N_AMMO_M_R,
	N_AMMO_S, N_AMMO_R, N_JETPACK, N_GEM_B, N_GEM_G, N_GEM_R, N_GEM_P, N_MAGNUM,
	N_SHOTGUN, N_RIFLE, N_RPG};
	char		*tmp;

	if (obj->is_pickable)
	{
		tmp = ft_strdup(tab[ref]);
		underscore_off_name(tmp, ft_strlen(tmp));
		tmp = ft_strrjoin(PICK_STRING, tmp);
		put_data(env, (t_font){WHITE, tmp, env->hud.font.text,
			(t_vtx){W / 2, H / 2}, W / 40, -1, -1});
		lt_release((void**)&tmp);
	}
	return (1);
}

int		print_description_object(t_env *e, int i, int j, int txt)
{
	int			x;
	int			y;
	t_vtx		s;
	const char	*str[DSCRIP_STR_INV] = {
		I_STRING_0, I_STRING_1, I_STRING_2, I_STRING_3, I_STRING_4, I_STRING_5,
		I_STRING_6, I_STRING_7, I_STRING_8, I_STRING_9, I_STRING_10,
		I_STRING_11, I_STRING_12, I_STRING_13};

	SDL_GetMouseState(&x, &y);
	if ((i = select_object(e->player.inventory.objects, (t_ixy){x, y},
	e->hud.inventory.objects, 6)) > -1)
		txt = e->player.inventory.objects[i].ref;
	else if ((j = select_object(e->player.inventory.gems, (t_ixy){x, y},
	e->hud.inventory.gems, 4)) > -1)
		txt = e->player.inventory.gems[j].ref;
	else if ((txt = select_wpn(e->player.inventory.weapons, (t_ixy){x, y},
	e->hud.inventory.wpn, 4)) > -1)
		txt = e->player.inventory.weapons[txt].ref + 10;
	else
		return (1);
	(txt < 6) ? s = (t_vtx){W / 6, H / 100} : (t_vtx){0, 0};
	(txt > 5 && txt < 10) ? s = (t_vtx){W / 5, H / 1.9} : (t_vtx){0, 0};
	(txt > 9) ? s = (t_vtx){W / 8, H / 1.9} : (t_vtx){0, 0};
	put_data(e, (t_font){WHITE, str[txt], e->hud.font.text, s, W / 40, -1, -1});
	return (1);
}

int		ui_txt_inv(t_env *env, int i, int r)
{
	const char	*str[7] = {D_LEVEL, D_SECTOR, D_KTOGO, STRING_19, STRING_20,
	STRING_21, STRING_22};
	const t_vtx	pos[4] = {{W / 40, H / 50}, {W / 40, H / 1.6},
		{W / 40, H / 2.15}, {W / 2.1, H / 1.4}};
	const t_vtx	stats[3] = {{W - (W / 3), H / 50}, {W - W / 3.3, H / 7},
		{W - W / 3.4, H / 4.9}};
	const float	size[3] = {W / 23, W / 30, W / 40};

	while (++i < 4)
	{
		put_data(env, (t_font){WHITE, str[r++],
			env->hud.font.doom, pos[i],
			i == 0 ? W / 20 : W / 34, -1, -1});
		if (i < 3)
			put_data(env, (t_font){i == 2 ? GOLD : WHITE, str[i],
			(i == 0) ? env->hud.font.doom : env->hud.font.text, stats[i],
			size[i], -1, env->stats.data[i]});
	}
	print_stats(env, W / 60,
		(t_vtx){W / 2.0, W / 1.4}, (t_vtx){H / 11, H / 36});
	return (print_description_object(env, -1, -1, 0));
}

int		ui_icon_data(t_env *env, t_vtx v, int iter)
{
	int				data;
	SDL_Color		c;
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
	put_data(env, (t_font){c, "%", env->hud.font.text,
	(t_vtx){v.x, v.y}, W / 45, data, -1});
	return (1);
}

int		ui_draw_msg(t_env *env, int *nb, int *tframe)
{
	t_font		d;
	t_vtx		pos;
	const char	*string[19] = {
	STRING_0, STRING_1, STRING_2, STRING_3, STRING_4, STRING_5, STRING_6,
	STRING_7, STRING_8, STRING_9, STRING_10, STRING_11, STRING_12, STRING_13,
	STRING_14, STRING_15, STRING_16, STRING_17, STRING_18};

	if (*nb && *nb < 19)
	{
		ft_bzero(&d, sizeof(t_font));
		pos = (t_vtx){W / 128, H - H / 2.5};
		d = (t_font){WHITE, string[*nb],
			env->hud.font.text, pos, W / 40, -1, -1};
		put_data(env, d);
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
