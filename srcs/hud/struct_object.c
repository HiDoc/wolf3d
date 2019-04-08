/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:41 by abaille           #+#    #+#             */
/*   Updated: 2019/04/08 11:48:44 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	underscore_off_name(char *name, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		name[i] == '_' ? name[i] = ' ' : 0;
	return (1);
}

char **tab_name_objects(void)
{
	char	**new;
	int		i;
	int		size;
	const char	*tab[WORLD_NB_OBJECTS] = {N_HEALTH, N_SHIELD, N_AMMO_M_R,
	N_AMMO_S, N_AMMO_R, N_JETPACK, N_GEM_B, N_GEM_G, N_GEM_R, N_GEM_P, N_MAGNUM,
	N_SHOTGUN, N_RIFLE, N_RPG};

	i =-1;
	if (!(new = malloc(sizeof(char **) * WORLD_NB_OBJECTS)))
		return (NULL);
	while (++i < WORLD_NB_OBJECTS)
	{
		if (!(new[i] = ft_strdup(tab[i])))
			return (NULL);
		size = ft_strlen(tab[i]);
		underscore_off_name(new[i], size);
	}
	return (new);
}

int	object_new(t_object *new, int i, int max_stack, t_l_float size)
{
	char		*name;
	int			ret;
	const char	*tab[WORLD_NB_OBJECTS] = {N_HEALTH, N_SHIELD, N_AMMO_M_R,
	N_AMMO_S, N_AMMO_R, N_JETPACK, N_GEM_B, N_GEM_G, N_GEM_R, N_GEM_P, N_MAGNUM,
	N_SHOTGUN, N_RIFLE, N_RPG};

	ret = 0;
	name = NULL;
	new->size = size;
    new->max_stack = max_stack;
	if ((name = ft_strjoin("consumable/", tab[i]))
	&& (name = ft_strljoin(name, "_"))
	&& (new->sprite = ui_img(name, i)))
		ret = 1;
	if (name)
		free(name);
    return (ret);
}

int	init_inventory(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		env->player.inventory.objects[i] = (t_wrap_inv) {NULL, 0, 0};
		i++;
	}
	env->hud.inventory.is_active = 0;
	return (1);
}

int	init_consumable(t_env *env)
{
	int	i;

	i = 0;
	env->hud.name_objects = tab_name_objects();
	while (i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_CSMBLE)
		{
			if (!object_new(&env->world.objects[i], i, i == 5 ? 1 : 5, (t_l_float){4, 3}))
				return (0);
		}
		else if (i > WORLD_NB_CSMBLE + WORLD_NB_GEMS)
		{
			if (!object_new(&env->world.objects[i], i, 0, (t_l_float){4, 2}))
				return (0);
		}
		else
		{
			if (!object_new(&env->world.objects[i], i, -1, (t_l_float){4, 1}))
				return (0);
		}
		env->world.objects[i].name = env->hud.name_objects[i];
		printf("%s\n", env->world.objects[i].name);
		i++;
	}
	env->hud.inventory.is_active = 0;
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
	printf("time consumable: %u\n", SDL_GetTicks());
	return (1);
}
