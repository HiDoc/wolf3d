/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/28 16:47:20 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	object_new(t_object *new, int i, int max_stack)
{
    new->max_stack = max_stack;
	if ((new->sprite = ui_img("consumable/", i)))
	    return (1);
    return (0);
}

int	init_consumable(t_env *env)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_CSMBLE)
		{
			if (!object_new(&env->world.objects[i], i, i == 5 ? 1 : 5))
				return (0);
		}
		else
		{
			if (!object_new(&env->world.objects[i], i, 0))
				return (0);
		}
		i++;
	}
	env->hud.inventory.is_active = 0;
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
	printf("time consumable: %u\n", SDL_GetTicks());
	return (1);
}
