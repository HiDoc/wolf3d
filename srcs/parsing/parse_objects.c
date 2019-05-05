/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:31 by abaille           #+#    #+#             */
/*   Updated: 2019/05/05 18:31:44 by abaille          ###   ########.fr       */
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

t_wrap_sect	*new_wrap(t_vtx curr, t_ixy ref_sect, int is_wpn)
{
	t_wrap_sect *new;

	new = ft_memalloc(sizeof(t_wrap_sect));
	ft_bzero(new, sizeof(t_wrap_sect));
	new->ref = ref_sect.x;
	new->sectorno = ref_sect.y;
	new->vertex = curr;
	new->is_wpn = is_wpn;
	(!is_wpn) ? pick_action(new) : 0;
	return (new);
}

void		fill_objects_sector(t_sector *s, t_vtx v, t_ixy ref_sct, int is_wpn)
{
	t_wrap_sect *iter;

	iter = NULL;
	if (s->head_object == NULL)
		s->head_object = new_wrap(v, ref_sct, is_wpn);
	else
	{
		iter = s->head_object;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new_wrap(v, ref_sct, is_wpn);
	}
	s->nb_objects++;
}
