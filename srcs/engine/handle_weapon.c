/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:32:57 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/28 13:44:05 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	handle_weapon(t_env *env, int *frame)
{
	t_bloc				*bloc;
	t_actions			*actions;
	const t_wrap_wpn	*curr = env->player.inventory.current;

	actions = &env->player.actions;
	if (curr)
	{
		if (actions->is_loading)
		{
			actions->is_shooting = !actions->is_shooting;
			put_gun_load(env, *frame);
			++(*frame);
		}
		else if (actions->is_shooting)
		{
			put_gun_shoot(env, *frame);
			++(*frame);
		}
		else if (curr)
		{
			bloc = &env->world.armory[curr->current->ref].sprite;
			put_gun(env, bloc);
			*frame = 0;
		}
	}
	return (0);
}
