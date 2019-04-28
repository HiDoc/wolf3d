/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:31 by abaille           #+#    #+#             */
/*   Updated: 2019/04/28 16:29:58 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			pick_action(t_wrap_sect *new)
{
	if (new->ref < 2)
		new->action = &give_life;
	if (new->ref > 1 && new->ref < 5)
		new->action = &give_ammo;
	if (new->ref == 5)
		new->action = &give_jetpack;
	return (0);
}

t_wrap_sect	*new_wrap(t_vtx curr, t_ixy ref_sect, int is_wpn, t_wrap_sect *prev)
{
	t_wrap_sect *new;

	new = ft_memalloc(sizeof(t_wrap_sect));
	new->ref = ref_sect.x;
	new->sectorno = ref_sect.y;
	new->vertex = curr;
	new->is_picked = 0;
	new->is_pickable = 0;
	new->is_wpn = is_wpn;
	new->next = NULL;
	new->prev = prev;
	if (!is_wpn)
		pick_action(new);
	return (new);
}

void		fill_objects_sector(t_sector *sector, t_vtx v, t_ixy ref_sect, int is_wpn)
{
	t_wrap_sect *iter;
	t_wrap_sect *prev;

	iter = NULL;
	prev = NULL;
	if (sector->head_object == NULL)
		sector->head_object = new_wrap(v, ref_sect, is_wpn, prev);
	else
	{
		iter = sector->head_object;
		while (iter->next != NULL)
		{
			prev = iter;
			iter = iter->next;
		}
		iter->next = new_wrap(v, ref_sect, is_wpn, prev);
	}
	sector->nb_objects++;
}
