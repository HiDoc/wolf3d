/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:32:04 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/05 19:25:54 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		action_bzero(t_action *new)
{
	new->is_shooting = 0;
	new->is_loading = 0;
	new->is_swimming = 0;
	new->is_flying = 0;
	new->is_jumping = 0;
	new->is_up_down = 0;
}

t_action	*action_new(void)
{
	t_actions *new;

	if ((t_action *)(malloc(sizeof(t_action))) == NULL)
		return (NULL);
	action_bzero(new);
	return (new);
}
