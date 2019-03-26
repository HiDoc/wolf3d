/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_inventory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:15:58 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 11:45:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	select_action(t_minibloc p, int x, int y)
{
	return (x >= p.rect.x && x <= p.rect.x + p.rect.w
	&& y >= p.rect.y && y <= p.rect.y + p.rect.h);
}

int	select_object(t_wrap_inv *object, int x, int y, t_bloc *p)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (x >= p[i].rect.x && x <= p[i].rect.x + p[i].rect.w && y >= p[i].rect.y && y <= p[i].rect.y + p[i].rect.h)
		{
			if (object[i].current)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	action_inventory(t_env *env, int x, int y)
{
	int			iter;
	int			index;
	SDL_Surface	*drag_sprite;
	t_wrap_inv	*object;
	t_bloc		*bloc;

	iter = -1;
	index = -1;
	drag_sprite = NULL;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
	{
		if ((index = select_object(env->player.inventory.objects, x, y, env->hud.inventory.objects)) > -1)
		{
			object = &env->player.inventory.objects[index];
			bloc = &env->hud.objects[index];
			if (select_action(bloc->cross, x, y))
				drop_object(env, object);
			// else if (select_action(bloc->use, x, y))
			// 	env->hud.is_txt = object->current->action((void*)env, object);
		}
		SDL_FlushEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP);
	}
	return (0);
}
