/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_inventory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:15:58 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 16:47:10 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			select_action(t_mbloc p, int x, int y)
{
	return ((x >= p.rect.x && x <= p.rect.x + p.rect.w)
	&& (y >= p.rect.y && y <= p.rect.y + p.rect.h));
}

int			select_object(t_wrap_inv *object, t_ixy xy, t_bloc *p, int limit)
{
	int i;

	i = 0;
	while (i < limit)
	{
		if (xy.x >= p[i].rect.x && xy.x <= p[i].rect.x + p[i].rect.w
		&& xy.y >= p[i].rect.y && xy.y <= p[i].rect.y + p[i].rect.h)
		{
			if (object[i].is_full)
				return (i);
		}
		i++;
	}
	return (-1);
}

int			select_wpn(t_wrap_wpn *wpn, t_ixy xy, t_bloc *p, int limit)
{
	int i;

	i = 0;
	while (i < limit)
	{
		if (xy.x >= p[i].rect.x && xy.x <= p[i].rect.x + p[i].rect.w
		&& xy.y >= p[i].rect.y && xy.y <= p[i].rect.y + p[i].rect.h)
		{
			if (wpn[i].is_full)
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	action_object(t_env *e, int index, int x, int y)
{
	t_bloc		*bloc;
	t_wrap_inv	*object;

	if ((index = select_object(e->player.inventory.objects, (t_ixy){x, y},
		e->hud.inventory.objects, 6)) > -1)
	{
		object = &e->player.inventory.objects[index];
		bloc = &e->hud.inventory.objects[index];
		if (select_action(bloc->cross, x, y))
			drop_object(e, object);
		else if (select_action(bloc->use, x, y))
			e->hud.is_txt = object->action((void*)e, object);
		return (1);
	}
	return (0);
}

void		action_inventory(t_env *e, int x, int y)
{
	int			iter;
	int			index;
	t_wrap_wpn	*weapon;
	t_bloc		*bloc;

	iter = -1;
	index = -1;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
	{
		if (!action_object(e, index, x, y)
			&& (index = select_wpn(e->player.inventory.weapons, (t_ixy){x, y},
			e->hud.inventory.wpn, 4)) > -1)
		{
			bloc = &e->hud.inventory.wpn[index];
			weapon = &e->player.inventory.weapons[index];
			if (select_action(bloc->cross, x, y))
				drop_wpn(e, weapon);
		}
	}
}
