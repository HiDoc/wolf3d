/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:33:40 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/27 18:17:12 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        export_map(t_env *env)
{
	t_sct	*sct;
	t_vtx	*vtx;
	char	*path;
	int		fd;

	if (!(path = lt_push(ft_strjoin("maps/", env->map_name), ft_memdel)))
		ui_error_exit_sdl("Editor: Error while opening file");

	if ((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ui_error_exit_sdl("Editor: Error while opening file");
	lt_release(path);

	ft_putendl_fd("# map name", fd);
	ft_putendl_fd(env->map_name, fd);

	ft_putendl_fd("# game misc: music skybox", fd);
	dprintf(fd, "%s %s\n", "music", "skybox");

	ft_putendl_fd("# vertex: x y", fd);
	vtx = env->vertex;
	while (vtx)
	{
		dprintf(fd, "vertex %d %d\n",
		(int)(vtx->pos.x), (int)(vtx->pos.y));
		vtx = vtx->next;
	}

	ft_putstr_fd("# sector: cl_h cl_tx fl_h fl_tx gravity type n-vtx", fd);
	sct = env->sct_start;
	while (sct)
	{
		dprintf(fd, "sector // //\n");
		sct = sct->next;	
	}

	/*ft_putendl_fd("# wall_object: x y sector ref", fd);
	obj = env->objects;
	while (obj)
	{
		if (obj->category == WALL_OBJ)
			//dprintf(fd, "wall_object %d %d // //\n",
			(int)(obj->pos.x - xmin),(int)(obj->pos.y - ymin));
		obj = obj->next;	
	}*/

	/*ft_putendl_fd("# consumable: x y sector ref is_wpn", fd);
	obj = env->objects;
	while (obj)
	{
		if (obj->category == CONSUMABLE)
			//dprintf(fd, "consumable %d %d // // //\n",
			(int)(obj->pos.x - xmin), (int)(obj->pos.y - ymin));
		obj = obj->next;	
	}*/
	
	/*ft_putendl_fd("# entity: x y sector ref", fd);	
	obj = env->objects;
	while (obj)
	{
		if (obj->category == ENTITY)
			//dprintf(fd, "entity %d %d // //\n",
			(int)(obj->pos.x - xmin), (int)(obj->pos.y - ymin));
		obj = obj->next;	
	}

	ft_putendl_fd("# special: x y ref", fd);
	obj = env->objects;
	while (obj)
	{
		if (obj->category == SPECIAL)
			//dprintf(fd, "special %d %d //\n",
			(int)(obj->pos.x - xmin), (int)(obj->pos.y - ymin));
		obj = obj->next;	
	}

	close(fd);*/
}
