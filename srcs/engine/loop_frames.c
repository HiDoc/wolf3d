/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:32:57 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/15 16:08:25 by abaille          ###   ########.fr       */
=======
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:32:57 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/11 15:32:58 by fmadura          ###   ########.fr       */
>>>>>>> 13425d09f94af12f2b96a6be41ffd46f01f947e0
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	loop_frames(t_env *env, int *frame)
{
	if (env->player.inventory.current)
	{
		if (env->player.actions.is_loading)
		{
			if (env->player.actions.is_shooting)
			{
				*frame = 0;
				env->player.actions.is_shooting = 0;
			}
			put_gun_load(env, *frame);
			++(*frame);
		}
		else if (env->player.actions.is_shooting)
		{
			put_gun(env,
			env->world.armory[env->player.inventory.current->current->ref].sprite_shoot);
			env->player.actions.is_shooting = 0;
			*frame = 0;
		}
		else
		{
			put_gun(env,
			env->world.armory[env->player.inventory.current->current->ref].sprite);
			*frame = 0;
		}
	}
	return (0);
}
