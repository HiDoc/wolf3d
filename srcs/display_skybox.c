/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_skybox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:56:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/12 22:06:43 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		display_skybox(t_env *env)
{
	int				w;
	int				h;
	float			player_d;
	float			yaw_d;
	float			wcalc;
	float			hcalc;

	player_d = (int)(env->engine.player.angle * 180 / M_PI) % 360;
	(player_d < 0) ? player_d = 360 + player_d : 0;

	yaw_d = (int)(env->engine.player.yaw * 180 / M_PI);

	w = 0;
	while (w < W)
	{
		wcalc = (w * (env->skybox.sb->w / 4)) / W;
		wcalc += (player_d * env->skybox.sb->w) / 360;
		wcalc = (int)wcalc % env->skybox.sb->w;
		h = 0;
		while (h < H)
		{
			hcalc = H;
			hcalc += (int)((h / 4) % env->skybox.sb->h);
			hcalc += (yaw_d * env->skybox.sb->h / 2) / 360;
			hcalc = (int)hcalc % env->skybox.sb->h;
			setpixel(env->sdl.surface, w, h,
			getpixel(env->skybox.sb, wcalc, hcalc));
			h++;
		}
		w++;
	}
}
