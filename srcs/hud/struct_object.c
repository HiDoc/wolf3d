/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:41 by abaille           #+#    #+#             */
/*   Updated: 2019/04/08 19:03:34 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	init_inventory(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		env->player.inventory.objects[i] = (t_wrap_inv) {NULL, 0, 0};
		i++;
	}
	env->hud.inventory.is_active = 0;
	return (1);
}
