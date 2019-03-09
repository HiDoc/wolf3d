#include "doom.h"

int			pick_action(t_wrap_sect *new)
{
	if (new->ref == 0)
		new->action = &give_health;
	else if (new->ref == 1)
		new->action = &give_shield;
	else if (new->ref > 1 && new->ref < 5)
		new->action = &give_ammo;
	return (0);
}

t_wrap_sect	*new_wrap(t_vtx curr, int ref)
{
	t_wrap_sect *new;

	if (!(new = malloc(sizeof(t_wrap_sect))))
		return (NULL);
	new->ref = ref;
	new->vertex = curr;
	new->is_picked = 0;
	new->next = NULL;
	pick_action(new);
	return (new);
}

int		fill_objects_sector(t_sector *sector, t_vtx v, int ref)
{
	t_wrap_sect *iter;

	iter = NULL;
	if (sector->head_object == NULL)
		sector->head_object = new_wrap(v, ref);
	else
	{
		iter = sector->head_object;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new_wrap(v, ref);
	}
	return (0);
}
