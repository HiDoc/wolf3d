/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:32:04 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/08 10:59:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_action	*action_new(void)
{
	t_actions *new;

	if ((t_action *)(malloc(sizeof(t_action))) == NULL)
		return (NULL);
	ft_bzero(new, sizeof(new));
	return (new);
}
