/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_skybox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:56:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/12 16:09:57 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		display_skybox(t_env *env)
{
	//const SDL_Surface		*sb_tab[4] = {
	//	env->skybox.sb_front, env->skybox.sb_right,
	//	env->skybox.sb_back, env->skybox.sb_left};
	int				w;
	int				h;
	int				wcalc;
	SDL_Surface		*srf;
	float			angle_d;

	angle_d = (int)(env->engine.player.angle * 180 / M_PI) % 360;
	(angle_d < 0) ? angle_d = 360 - ((int)fabs(angle_d) % 360) : 0;

	srf = env->skybox.sb_front;

	w = 0;
	while (w < W)
	{
		wcalc = (w * srf->w) / W;
		h = 0;
		while (h < H)
		{
			setpixel(env->sdl.surface, w, h,
			getpixel(srf, wcalc, h));
			h++;
		}
		w++;
	}
}

//
//	0	  W
//	[|||||] [|||||] [|||||] [|||||]
//	0	  90	  180	  270	  360
//
