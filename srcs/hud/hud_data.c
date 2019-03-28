/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:57 by abaille           #+#    #+#             */
/*   Updated: 2019/03/28 15:03:21 by abaille          ###   ########.fr       */
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
	t_wrap_inv	*object;

	i = 0;
	SDL_GetMouseState(&x, &y);
	if ((i = select_object(env->player.inventory.objects, x, y,
	env->hud.inventory.objects)) > -1)
	{
		object = &env->player.inventory.objects[i];
		env->hud.txt_inv = object->current->ref;
	}
	else
		env->hud.txt_inv = 11;
	draw_scaled_string((t_font){WHITE, "Infos Object inventory",
	env->hud.text.text, (t_vtx){W / 40, H / 6.7}, W / 50, -1, -1},
	env->hud.text.i_obj_description[env->hud.txt_inv], env->sdl.surface, (t_vtx){0, 0});
	return (1);
}

int     ui_txt_inv(t_env *env)
{
	draw_scaled_string((t_font){WHITE, "Inventory",
	env->hud.text.doom, (t_vtx){W / 40, H / 50}, W / 16, -1, -1},
	env->hud.text.t_inv[0], env->sdl.surface, (t_vtx){0, 0});
	draw_scaled_string((t_font){WHITE, "Weapons",
	env->hud.text.doom, (t_vtx){W / 40, H / 1.7}, W / 26, -1, -1},
	env->hud.text.t_inv[1], env->sdl.surface, (t_vtx){0, 0});
	ui_put_data(env, (t_font){WHITE, "Level : ", env->hud.text.doom,
	(t_vtx){W - (W / 3), H / 50}, W / 16, -1, 1});
    ui_put_data(env, (t_font){BLUE, "Sector : ", env->hud.text.text,
	(t_vtx){W - W / 3.2, H / 6}, W / 30, -1, env->engine.player.sector});
    ui_put_data(env, (t_font){RED, "Enemies to kill : ", env->hud.text.text,
	(t_vtx){W - W / 3.1, H / 4.5}, W / 40, -1, 1});
	print_description_object(env);
    return (1);
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
