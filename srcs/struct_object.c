/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:34:47 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/05 17:34:50 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void        object_bzero(t_object *new)
{
    new->sprite = NULL;
    new->is_consumable = 0;
    new->nb_use = 0;
}

t_object *object_new(void)
{
    t_objects *new;

    if ((t_object *)(malloc(sizeof(t_object))) == NULL)
        return (NULL);
    object_bzero(new);
    return (new);
}