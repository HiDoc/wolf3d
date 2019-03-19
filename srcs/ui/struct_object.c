/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 21:53:01 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	object_new(t_object *new, char *res, int i, int max_stack)
{
    new->max_stack = max_stack;
	if ((new->sprite = ui_img(res, "consumable/", "", i)))
	    return (1);
    return (0);
}

int	init_inventory(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		env->player.inventory.objects[i] = (t_wrap_inv) {NULL, 0, 0, {{{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}}};
		i++;
	}
	env->player.inventory.ui.is_active = 0;
	return (1);
}

int	init_consumable(t_env *env, char *res)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		if (!object_new(&env->world.objects[i], res, i, i == 5 ? 1 : 5))
			return (0);
		i++;
	}
	return (init_inventory(env));
}
