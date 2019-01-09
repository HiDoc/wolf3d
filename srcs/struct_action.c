/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 12:23:48 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/09 13:02:03 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf.h"

t_action	*action_new(void)
{
	t_action *new;

	if ((new =(t_action *)(malloc(sizeof(t_action)))) == NULL)
		return (NULL);
	ft_bzero(new, sizeof(t_action));
	return (new);
}
