/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:57 by abaille           #+#    #+#             */
/*   Updated: 2019/03/20 18:36:11 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int    ui_put_fps(t_env *env, int fps)
{
	ui_put_string(env, (t_font){RED, "fps : ", env->ui.number, (t_vtx){10, 10}, 20, -1, fps});
    return (1);
}

int     ui_txt_inv(t_env *env)
{
	ui_put_string(env, (t_font){WHITE, "Inventory", env->ui.doom, (t_vtx){20, 15}, 50, -1, -1});
	ui_put_string(env, (t_font){WHITE, "Weapons", env->ui.doom, (t_vtx){20, H / 1.7}, 30, -1, -1});
	ui_put_string(env, (t_font){WHITE, "Level : ", env->ui.doom, (t_vtx){W - (W / 3), 15}, 50, -1, 1});
    ui_put_string(env, (t_font){BLUE, "Sector : ", env->ui.text, (t_vtx){W - W / 3.2, 95}, 25, -1, env->engine.player.sector});
    ui_put_string(env, (t_font){RED, "Enemies to kill : ", env->ui.text, (t_vtx){W - W / 3.1, 125}, 20, -1, 1});
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
	ui_put_string(env, (t_font){c, "%", env->ui.text, (t_vtx){v.x + 15, v.y + 8}, 28, data, -1});
	return (1);
}

int	ui_text_msg(t_env *env, char *msg)
{
	ui_put_string(env, (t_font){(SDL_Color){255, 255, 255, 255}, msg,
	env->ui.text, (t_vtx){50, H - H / 2.5}, 20, -1, -1});
	return (0);
}

int	ui_draw_msg(t_env *env, int *nb, int *tframe)
{
	if (*nb)
	{
		if (*nb == 1)
			ui_text_msg(env, "Already full shield !");
		else if (*nb == 2)
			ui_text_msg(env, "No shield in stock, stop crying & find some");
		else if (*nb == 3)
			ui_text_msg(env, "Already full of life, enjoy mate !");
		else if (*nb == 4)
			ui_text_msg(env, "No heal in stock, hang on !");
		else if (*nb == 5)
			ui_text_msg(env, "Too greedy man.. Already full stack of this item");
		else if (*nb == 6)
			ui_text_msg(env, "New item placed in inventory");
		else if (*nb == 7)
			ui_text_msg(env, "Inventory full - Max 6 different items");
		else if (*nb == 8)
			ui_text_msg(env, "Item suppressed from inventory");
		else if (*nb == 9)
			ui_text_msg(env, "Weapon already full");
		else if (*nb == 10)
			ui_text_msg(env, "No ammo for this weapon");
		else if (*nb == 11)
			ui_text_msg(env, "JetPack ON");
		else if (*nb == 12)
			ui_text_msg(env, "JetPack OFF");
		else if (*nb == 13)
			ui_text_msg(env, "No JetPack here, keep looking bro !");
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
