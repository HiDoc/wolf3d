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

t_object *object_new(void)
{
    t_object *new;

    if ((new = (t_object *)(malloc(sizeof(t_object)))) == NULL)
        return (NULL);
    ft_bzero(new, sizeof(t_object));
    return (new);
}