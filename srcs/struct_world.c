/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:33:08 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/24 16:09:09 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void    init_container(t_container *container)
{
    int     i;
    char    *filename;

    i = 1;
    while (i < 6)
    {
        filename = ft_strrjoin("walls/0", ft_itoa(i));
        container->walls[i - 1].sprite = img_new(filename);
        free(filename);
        filename = NULL;
        i++;
    }
    i = 1;
    while (i < 5)
    {
        filename = ft_strrjoin("floor/0", ft_itoa(i));
        container->floors[i - 1].sprite = img_new(filename);
        free(filename);
        filename = NULL;
        i++;
    }
}

void    init_world(t_env *env)
{
    t_world     *world;
    t_container *surfaces;

    world = &env->world;
    surfaces = &env->world.surfaces;
    init_container(surfaces);
}