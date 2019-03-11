#include "doom.h"

int			pick_action(t_wrap_sect *new)
{
	if (new->ref == 0)
		new->action = &give_health;
	if (new->ref == 1)
		new->action = &give_shield;
	if (new->ref > 1 && new->ref < 5)
		new->action = &give_ammo;
	if (new->ref == 5)
		new->action = &give_jetpack;
	return (0);
}

t_wrap_sect	*new_wrap(t_vtx curr, int ref, int is_wpn)
{
	t_wrap_sect *new;

	if (!(new = malloc(sizeof(t_wrap_sect))))
		return (NULL);
	new->ref = ref;
	new->vertex = curr;
	new->is_picked = 0;
	new->is_wpn = is_wpn;;
	new->next = NULL;
	if (!is_wpn)
		pick_action(new);
	return (new);
}

int		fill_objects_sector(t_sector *sector, t_vtx v, int ref, int is_wpn)
{
	t_wrap_sect *iter;

	iter = NULL;
	if (sector->head_object == NULL)
		sector->head_object = new_wrap(v, ref, is_wpn);
	else
	{
		iter = sector->head_object;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new_wrap(v, ref, is_wpn);
	}
	return (0);
}