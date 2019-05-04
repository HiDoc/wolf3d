/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:23:47 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/04 20:16:42 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ft_strchri(char *str, char c)
{
	int count;

	count = 0;
	while (str[count])
	{
		if (str[count] == c)
			return (count);
		count++;
	}
	return (-1);
}

static void		init_pack_img(t_surface *pack, char *path)
{
	char				*name;
	struct dirent		*de;
	DIR					*dr;
	int					i;

	i = 0;
	if (!(dr = lt_push(opendir(path), dir_del)))
		doom_error_exit("Doom_nukem: init_pack_img, unable to open path");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			name = ft_strjoin(path, de->d_name);
			pack[i].sprite = load_image(name);
			lt_release((void**)&name);
			i++;
		}
	}
	lt_release((void **)&dr);
}

static void		init_consumable(char *path, int type, t_env *env)
{
	char				*name;
	struct dirent		*de;
	int					ref;
	DIR					*dr;

	if (!(dr = lt_push(opendir(path), dir_del)))
		doom_error_exit("Doom_nukem: init_pack_img, unable to open path");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			if (!(name = lt_push(ft_strsub(
					de->d_name, 0, ft_strchri(de->d_name, '+')), ft_memdel)))
				doom_error_exit("Doom_nukem: Out of memory init_consumable");
			ref = ft_atoi(ft_strchr(de->d_name, '+'));
			name = ft_strjoin(path, de->d_name);
			env->world.objects[ref].sprite = load_image(name);
			if (type == 0) // object
			{
				env->world.objects[ref].max_stack = (ref == 5) ? 1 : 5;
				env->world.objects[ref].size = (t_l_float){8, 3};
			}
			else if (type == 1) // special
			{
				env->world.objects[ref].max_stack = 0;
				env->world.objects[ref].size = (t_l_float){7, 2};
			}
			else if (type == 2) // gem
			{
				env->world.objects[ref].max_stack = -1;
				env->world.objects[ref].size = (t_l_float){6, 1};
			}
			lt_release((void**)&name);
		}
	}
	lt_release((void **)&dr);
	ft_bzero(&env->player.inventory, sizeof(t_inventory));
	printf("time consumable: %u\n", SDL_GetTicks());
}

static void			init_character(t_character *new)
{
	ft_bzero(&new->actions, sizeof(new));
	new->max_health = 200;
	new->max_shield = 200;
}

void				load_images(t_env *env)
{
	init_pack_img(env->world.surfaces.poster, "rsrc/img/posters/");
	init_pack_img(env->world.surfaces.walls, "rsrc/img/walls/");
	init_pack_img(env->world.surfaces.floors, "rsrc/img/floors/");
	init_pack_img(env->world.surfaces.hud, "rsrc/img/hud/");
	init_pack_img(env->world.surfaces.img_menu, "rsrc/img/menu/");
	init_consumable("rsrc/img/consumable/objects/", 0, env);
	init_consumable("rsrc/img/consumable/specials/", 1, env);
	init_consumable("rsrc/img/consumable/gems/", 2, env);
	init_character(&env->player);
	env->skybox.sb = load_image("rsrc/skybox/sb.jpg");
	env->engine.player.sprite = ui_img("bullet/", 0);
}
