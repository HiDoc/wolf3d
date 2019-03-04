#include "doom.h"

SDL_Surface *img_consumable(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/consumable/", filename);
	path = ft_strljoin(path, (char *)png);
	new = create_surf(path);
	free(path);
	path = NULL;
	return (new);
}

int         object_new(t_object *new, char *filename, int max_stack)
{
    new->max_stack = max_stack;
	if ((new->sprite = img_consumable(filename)))
	    return (1);
    return (0);
}

int			init_inventory(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		env->player.inventory.objects[i] = (t_wrap_inv) {NULL, 0, 0, {{{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}}, NULL, {0, 0}, 0, {{0, 0}, {0, 0}}};
		i++;
	}
	env->player.inventory.is_active = 0;
	return (0);
}

int         init_consumable(t_env *env)
{
	return (object_new(&env->world.objects[0], "kit3", 3)
	&& object_new(&env->world.objects[1], "armor2", 3)
	&& object_new(&env->world.objects[2], "ammo_1", 5)
	&& object_new(&env->world.objects[3], "ammo_2", 5)
	&& object_new(&env->world.objects[4], "ammo_3", 5)
	&& object_new(&env->world.objects[5], "jetpack", 1)
	&& init_inventory(env));
}
