/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:18:20 by fmadura           #+#    #+#             */
/*   Updated: 2018/12/11 16:19:56 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	load_weapon(t_env *env, Uint8 keycode, SDL_Surface **weapon)
{
	(void)weapon;
	if (keycode == SDL_SCANCODE_R)
	{
		env->ld_wp = 1;
		SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	}
	return (0);
}
