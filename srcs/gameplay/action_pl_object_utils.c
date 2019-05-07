/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_object_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:53:25 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 17:44:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	get_inventory_place(t_env *env)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!env->player.inventory.objects[i].is_full)
			return (i);
		i++;
	}
	return (i);
}

int	check_object_type(t_wrap_inv *pack, int ref, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (pack[i].is_full)
		{
			if (ref == pack[i].ref)
				return (i);
		}
		i++;
	}
	return (-1);
}
