/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 20:24:40 by abaille           #+#    #+#             */
/*   Updated: 2019/04/27 19:42:09 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


static void	concat_data(char **d, int nb, int endflag, char *entete)
{
	char	*tmp;

	tmp = ft_itoa(nb);
	entete ? tmp = ft_strrjoin(entete, tmp) : 0;
	tmp = !endflag ? ft_strljoin(tmp, ":") : ft_strljoin(tmp, "\n");
	*d = *d ? ft_strljoin(*d, tmp) : ft_strdup(tmp);
	lt_release((void**)&tmp);
}

static void	print_data(int fd, char **data)
{
	if (*data)
	{
		write(fd, *data, ft_strlen(*data));
		lt_release((void**)&*data);
		*data = NULL;
	}
}

void	save_data_file(t_env *e, char *name)
{
	char	*data;
	char	*tmp;
	int		fd;
	int		i;

	tmp = ft_itoa(e->menu.status.nb_save);
	data = ft_strjoin("./rsrc/save/", tmp);
	if ((fd = open(data, O_CREAT | O_TRUNC | O_WRONLY,
    	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		doom_error_exit("Doom_nukem error on create file save");
	lt_release((void**)&data);
	data = NULL;
	ft_putendl_fd(tmp, fd);
	lt_release((void**)&tmp);
	ft_putendl_fd(name, fd);
	concat_data(&data, e->engine.player.sector, 0, "#p:");
	concat_data(&data, e->player.health, 0, NULL);
	concat_data(&data, e->player.shield, 0, NULL);
	concat_data(&data, e->engine.player.where.x, 0, NULL);
	concat_data(&data, e->engine.player.where.y, 1, NULL);
	print_data(fd, &data);
	concat_data(&data, e->player.inventory.current->current->ref, 1, "#c:");
	print_data(fd, &data);
	i = -1;
	while (++i < GAME_NB_WPN)
	{
		if (e->player.inventory.weapons[i].current)
		{
			concat_data(&data, e->player.inventory.weapons[i].current->ref, 0, "#w:");
			concat_data(&data, e->player.inventory.weapons[i].ammo[0], 0, NULL);
			concat_data(&data, e->player.inventory.weapons[i].ammo[1], 0, NULL);
			concat_data(&data, e->player.inventory.weapons[i].ammo[2], 1, NULL);
		}
	}
	print_data(fd, &data);
	i = -1;
	while (++i < 6)
	{
		if (e->player.inventory.objects[i].current)
		{
			concat_data(&data, e->player.inventory.objects[i].current->ref, 0, "#o:");
			concat_data(&data, e->player.inventory.objects[i].nb_stack, 1, NULL);
		}
	}
	print_data(fd, &data);
	i = -1;
	while (++i < 4)
	{
		if (e->player.inventory.gems[i].current)
		{
			concat_data(&data, e->player.inventory.gems[i].current->ref, 0, "#g:");
			concat_data(&data, e->player.inventory.gems[i].nb_stack, 1, NULL);
		}
	}
	print_data(fd, &data);
	i = -1;
	while (++i < NB_STATS)
		concat_data(&data, e->stats.data[i], i == NB_STATS - 1 ? 1 : 0, i == 0 ? "#s:" : NULL);
	print_data(fd, &data);
	i = 0;
	while (++i < NB_OPT_KEY)
		concat_data(&data, e->engine.keys[i], i == NB_OPT_KEY - 1 ? 1 : 0, i == 1 ? "#k:" : NULL);
	print_data(fd, &data);
	i = -1;
	int j = -1;
	while (++i < (int)e->engine.nsectors)
	{
		t_wrap_sect	*obj = e->engine.sectors[i].head_object;
		while (obj)
		{
			j = -1;
			if (++j < e->engine.sectors[i].nb_objects)
			{
				j == 0 ? concat_data(&data, i, 0, "#s") : 0;
				concat_data(&data, obj->ref, 0, "o:");
				concat_data(&data, obj->is_wpn, 0, NULL);
				concat_data(&data, obj->is_picked, 0, NULL);
				concat_data(&data, obj->vertex.x, 0, NULL);
				concat_data(&data, obj->vertex.y, 1, NULL);
			}
			obj = obj->next;
		}
		print_data(fd, &data);
		t_wrap_enmy	*en = e->engine.sectors[i].head_enemy;
		while (en)
		{
			j = -1;
			if (en->is_alive && ++j < e->engine.sectors[i].nb_enemies)
			{
				j == 0 ? concat_data(&data, i, 0, "#s") : 0;
				concat_data(&data, en->ref, 0, "e:");
				concat_data(&data, en->brain.health, 0, NULL);
				concat_data(&data, en->player.where.x, 0, NULL);
				concat_data(&data, en->player.where.y, 1, NULL);
			}
			en = en->next;
		}
		print_data(fd, &data);
	}

	close(fd);
}