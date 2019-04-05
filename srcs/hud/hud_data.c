/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:57 by abaille           #+#    #+#             */
/*   Updated: 2019/04/05 16:42:09 by abaille          ###   ########.fr       */
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
	if (obj->is_pickable)
		draw_scaled_string((t_font){WHITE, "Pick Object Info",
		env->hud.text.text, (t_vtx){W / 2, H / 2}, W / 40, -1, -1},
		env->hud.text.pick_objects[ref], env->sdl.surface, (t_vtx){0, 0});
	return (1);
}

int		print_description_object(t_env *env)
{
	int	i;
	int	x;
	int	y;
	int	j;

	i = -1;
	j = -1;
	SDL_GetMouseState(&x, &y);
	if ((i = select_object(env->player.inventory.objects, (t_ixy){x, y},
	env->hud.inventory.objects, 6)) > -1)
		env->hud.txt_inv = env->player.inventory.objects[i].current->ref;
	else if ((j = select_object(env->player.inventory.gems, (t_ixy){x, y},
	env->hud.inventory.gems, 4)) > -1)
		env->hud.txt_inv = env->player.inventory.gems[j].current->ref;
	else
		return (1);
	draw_scaled_string((t_font){WHITE, "Infos Object inventory",
	env->hud.text.text, (t_vtx){i > -1 ? W / 40 : W / 10, i > -1 ? H / 7.05 : H / 2.1}, W / 50, -1, -1},
	env->hud.text.i_obj_description[env->hud.txt_inv], env->sdl.surface, (t_vtx){0, 0});
	return (1);
}

int		print_stats(t_env *env)
{
	env->stats.kill_togo = env->engine.sectors[env->engine.player.sector].nb_enemies;
	return (ui_put_data(env, (t_font){WHITE, "Level : ", env->hud.text.doom,
	(t_vtx){W - (W / 3), H / 50}, W / 23, -1, 1})
	&& ui_put_data(env, (t_font){GOLD, "Sector : ", env->hud.text.text,
	(t_vtx){W - W / 3.3, H / 7}, W / 30, -1, env->engine.player.sector})
    && ui_put_data(env, (t_font){RED, "Kills to go : ", env->hud.text.text,
	(t_vtx){W - W / 3.4, H / 4.9}, W / 40, -1, env->stats.kill_togo})
    && ui_put_data(env, (t_font){GOLD, "Enemies killed : ", env->hud.text.text,
	(t_vtx){W - W / 1.9, H / 1.25}, W / 60, -1, env->stats.k_enemies})
    && ui_put_data(env, (t_font){GOLD, "Death number : ", env->hud.text.text,
	(t_vtx){W - W / 1.9, H / 1.2}, W / 60, -1, env->stats.death})
    && ui_put_data(env, (t_font){GOLD, "Playing for : ", env->hud.text.text,
	(t_vtx){W - W / 1.9, H / 1.15}, W / 60, -1, env->stats.time_play})
    && ui_put_data(env, (t_font){GOLD, "Fists kills : ", env->hud.text.text,
	(t_vtx){W - W / 1.9, H / 1.1}, W / 60, -1, env->stats.k_wpn[FIST]})
    && ui_put_data(env, (t_font){GOLD, "Magnum kills : ", env->hud.text.text,
	(t_vtx){W - W / 3.0, H / 1.25}, W / 60, -1, env->stats.k_wpn[MAGNUM]})
    && ui_put_data(env, (t_font){GOLD, "Shotgun kills : ", env->hud.text.text,
	(t_vtx){W - W / 3.0, H / 1.2}, W / 60, -1, env->stats.k_wpn[SHOTGUN]})
    && ui_put_data(env, (t_font){GOLD, "Rifle kills : ", env->hud.text.text,
	(t_vtx){W - W / 3.0, H / 1.15}, W / 60, -1, env->stats.k_wpn[RIFLE]})
    && ui_put_data(env, (t_font){GOLD, "RPG-7 kills : ", env->hud.text.text,
	(t_vtx){W - W / 3.0, H / 1.10}, W / 60, -1, env->stats.k_wpn[RPG]}));
}

int     ui_txt_inv(t_env *env)
{
	draw_scaled_string((t_font){WHITE, "Inventory",
	env->hud.text.doom, (t_vtx){W / 40, H / 50}, W / 20, -1, -1},
	env->hud.text.t_inv[0], env->sdl.surface, (t_vtx){0, 0});
	draw_scaled_string((t_font){WHITE, "Weapons",
	env->hud.text.doom, (t_vtx){W / 40, H / 1.6}, W / 34, -1, -1},
	env->hud.text.t_inv[1], env->sdl.surface, (t_vtx){0, 0});
	draw_scaled_string((t_font){WHITE, "Gems",
	env->hud.text.doom, (t_vtx){W / 40, H / 2.15}, W / 34, -1, -1},
	env->hud.text.t_inv[4], env->sdl.surface, (t_vtx){0, 0});
	draw_scaled_string((t_font){WHITE, "Stats",
	env->hud.text.doom, (t_vtx){W / 2.2, H / 1.4}, W / 34, -1, -1},
	env->hud.text.t_inv[5], env->sdl.surface, (t_vtx){0, 0});
    return (print_stats(env)
	&& print_description_object(env));
}

int		ui_icon_data(t_env *env, t_vtx v, int iter)
{
	int				data;
	SDL_Color 		c;
	const SDL_Color	clrs[4] = {
		{8, 255, 8, 255},
		{42, 204, 242, 255},
		{242, 204, 42, 255},
		{255, 0, 0, 255}};

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
	ui_put_data(env, (t_font){c, "%", env->hud.text.text, (t_vtx){v.x, v.y}, W / 45, data, -1});
	return (1);
}

int	ui_draw_msg(t_env *env, int *nb, int *tframe)
{
	if (*nb && env->hud.text.string[*nb])
	{
		draw_scaled_string((t_font){WHITE, "coucou",
		env->hud.text.text, (t_vtx){50, H - H / 2.5}, W / 40, -1, -1},
		env->hud.text.string[*nb], env->sdl.surface, (t_vtx){0, 0});
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
