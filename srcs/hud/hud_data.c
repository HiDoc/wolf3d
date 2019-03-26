/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:57 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 11:45:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int    ui_put_fps(t_env *env, int fps)
{
	ui_put_data(env, (t_font){RED, "fps : ", env->hud.text.number, (t_vtx){10, 10}, 20, -1, fps});
    return (1);
}

int     ui_txt_inv(t_env *env)
{
	draw_scaled_string((t_font){WHITE, "inventory",
	env->hud.text.doom, (t_vtx){W / 40, 15}, W / 16, -1, -1},
	env->hud.text.t_inv[0], env->sdl.surface, (t_vtx){0, 0});
	draw_scaled_string((t_font){WHITE, "weapons",
	env->hud.text.doom, (t_vtx){W / 40, H / 2}, W / 26, -1, -1},
	env->hud.text.t_inv[1], env->sdl.surface, (t_vtx){0, 0});
	ui_put_data(env, (t_font){WHITE, "Level : ", env->hud.text.doom,
	(t_vtx){W - (W / 3), 15}, 50, -1, 1});
    ui_put_data(env, (t_font){BLUE, "Sector : ", env->hud.text.text,
	(t_vtx){W - W / 3.2, 95}, 25, -1, env->engine.player.sector});
    ui_put_data(env, (t_font){RED, "Enemies to kill : ", env->hud.text.text,
	(t_vtx){W - W / 3.1, 125}, 20, -1, 1});
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
	ui_put_data(env, (t_font){c, "%", env->hud.text.text, (t_vtx){v.x + 15, v.y + 8}, 28, data, -1});
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
