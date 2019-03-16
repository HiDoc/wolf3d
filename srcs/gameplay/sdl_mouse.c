/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/15 16:17:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	mouse_shoot(t_env *env)
{
    int x;
    int y;

    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1)
	&& env->player.inventory.current
	&& !env->player.inventory.ui.is_active
	&& !env->player.actions.is_loading)
	{
		if (env->player.inventory.current->ammo_current)
		{
			env->player.actions.is_shooting = !env->player.actions.is_shooting;
			// Mix_PlayChannel(-1, env->sounds.shot, 0);
			env->player.inventory.current->ammo_current--;
		}
		else
			load_weapon(env);
	}
	SDL_FlushEvent(SDL_MOUSEBUTTONUP);
	return (0);
}