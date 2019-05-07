/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:32:57 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/07 16:07:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	handle_weapon(t_env *e)
{
	t_actions			*actions;
	t_bloc				*bloc;

	actions = &e->player.actions;
	if (e->player.inventory.current->is_full)
	{
		if (actions->is_loading)
		{
			put_gun_load(e, e->time.frame);
			e->time.frame++;
		}
		else if (actions->is_shooting)
		{
			put_gun_shoot(e, e->time.frame);
			e->time.frame++;
		}
		else
		{
			bloc = &e->world.armory[e->player.inventory.current->ref].sprite;
			put_gun(e, bloc);
			e->time.frame = 0;
		}
	}
	return (0);
}
