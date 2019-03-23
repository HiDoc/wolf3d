/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_inventory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:15:58 by abaille           #+#    #+#             */
/*   Updated: 2019/03/23 15:14:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	select_action(t_edge *p, int x, int y)
{
	int i;

	i = 0;
	while (i < 2)
	{
		if (x >= p[i].v1.x && x <= p[i].v2.x && y >= p[i].v1.y && y <= p[i].v2.y)
			return (i);
		i++;
	}
	return (-1);
}

int	select_object(t_wrap_inv *object, int x, int y, t_edge *p)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (x >= p[i].v1.x && x <= p[i].v2.x && y >= p[i].v1.y && y <= p[i].v2.y)
		{
			if (object[i].current)
				return (i);
		}
		i++;
	}
	return (-1);
}

// int	action_inventory(t_env *env, int x, int y)
// {
// 	int			iter;
// 	int			index;
// 	SDL_Surface	*drag_sprite;
// 	t_wrap_inv	*object;

// 	iter = -1;
// 	index = -1;
// 	drag_sprite = NULL;
// 	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
// 	{
// 		if ((index = select_object(env->player.inventory.objects, x, y, env->player.inventory.ui.blocs)) > -1)
// 		{
// 			object = &env->player.inventory.objects[index];
// 			if ((iter = select_action(object->udbox, x, y)) == 1)
// 				env->player.hud.is_txt = object->current->action((void*)env, object);
// 			else if ((iter = select_action(object->udbox, x, y)) == 0)
// 				drop_object(env, object);
// 		}
// 		SDL_FlushEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP);
// 	}
// 	return (0);
// }
