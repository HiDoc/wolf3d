/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_decor_images.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 23:37:56 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 15:29:32 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	init_doors_images(t_env *e)
{
	int	i;

	i = -1;
	while (++i < NB_DOOR_IMG)
	{
		if (!(e->world.surfaces.doors[i].sprite = ui_img("decor/door/", i, 0)))
			return (0);
	}
	return (1);
}
