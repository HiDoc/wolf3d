/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:41 by abaille           #+#    #+#             */
/*   Updated: 2019/04/09 11:12:57 by abaille          ###   ########.fr       */
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

SDL_Surface **tab_name_objects(t_env *env, int i, t_vtx new_size)
{
	const char	*tab[WORLD_NB_OBJECTS] = {N_HEALTH, N_SHIELD, N_AMMO_M_R,
	N_AMMO_S, N_AMMO_R, N_JETPACK, N_GEM_B, N_GEM_G, N_GEM_R, N_GEM_P, N_MAGNUM,
	N_SHOTGUN, N_RIFLE, N_RPG};
	SDL_Surface	**new;
	SDL_Surface	*tmp;
	char		*name;

	if (!(new = malloc(sizeof(SDL_Surface**) * WORLD_NB_OBJECTS)))
		return (NULL);
	while (++i < WORLD_NB_OBJECTS)
	{
		tmp = NULL;
		name = NULL;
		if (!(name = ft_strdup(tab[i])))
			return (NULL);
		underscore_off_name(name, ft_strlen(name));
		if (!(tmp = ui_create_simple_string((t_font){WHITE,
		name, env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1})))
			return(NULL);
		new_size = (t_vtx){tmp->w / (100 / (W / 40)), tmp->h / (100 / (W / 40))};
		if (!(new[i] = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
		0xff000000, 0xff0000, 0xff00, 0xff)))
			return (NULL);
		ui_scaled_copy(tmp, new[i]);
		if (name)
			free(name);
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
	env->hud.text.obj_names = tab_name_objects(env, -1, (t_vtx){0, 0});
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
		i++;
	}
	env->hud.inventory.is_active = 0;
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
	printf("time consumable: %u\n", SDL_GetTicks());
	return (1);
}
