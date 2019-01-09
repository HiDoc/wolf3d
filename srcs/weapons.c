/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:18:20 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/08 14:48:00 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	load_weapon(t_env *env, Uint8 keycode, SDL_Surface **weapon)
{
	(void)weapon;
	if (keycode == SDL_SCANCODE_R)
	{
		env->player.actions.is_loading = 1;
		SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	}
	return (0);
}

int	shoot_weapon(t_env *env, int frame)
{
	SDL_Rect	rect;
	t_point		start;
	t_point		end;

	rect.w = 0;
	rect.h = 0;
	rect.x = 200;
	rect.y = 170;
	if (frame < 8)
	{
		//if (SDL_BlitSurface(env->mitra_frms[frame], NULL, env->sdl.surface, &rect) < 0)
		//	printf("SDL_blits failed: %s\n", SDL_GetError());
		start.x = 520;
		start.y = 430;
		end.x = 400;
		end.y = 300;
		surface_drawline(env->sdl.surface, start, end, 0xFF000000);
	}
	else
		env->player.actions.is_shooting = 0;
	return (0);
}
