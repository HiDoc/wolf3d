/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:33:40 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/04 15:17:16 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        export_map(t_env *env)
{
	t_sct		*sct;
	t_w_vtx		*w_vtx;
	t_vtx		*vtx;
	t_object	*obj;
	char		*path;
	int			fd;
	int			i;

	if (!(path = lt_push(ft_strjoin("maps/", env->map_name), ft_memdel)))
		ui_error_exit_sdl("Editor: Error while opening file");

	if ((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ui_error_exit_sdl("Editor: Error while opening file");
	lt_release((void**)&path);

	// map name
	ft_putendl_fd("# map name", fd);
	ft_putendl_fd(env->map_name, fd);

	// meta
	ft_putendl_fd("# background music", fd);
	dprintf(fd, "m %d\n", env->editor.dropdown[DD_BGAUDIO].current->ref);
	ft_putendl_fd("# skybox texture", fd);
	dprintf(fd, "b %d\n", env->editor.dropdown[DD_SBTX].current->ref);

	// vertex
	ft_putendl_fd("# vertex: x y", fd);
	i = 0;
	vtx = env->editor.vertex;
	while (vtx)
	{
		vtx->id = i;
		dprintf(fd, "v %d %d\n",
		(int)(vtx->pos.x), (int)(vtx->pos.y));
		vtx = vtx->next;
		i++;
	}

	// sectors
	dprintf(fd, "# sector: cl_h cl_tx fl_h fl_tx gravity roof type n-vtx n-tx\n");
	i = 0;
	sct = env->editor.sct_start;
	while (sct)
	{
		sct->id = i;
		dprintf(fd, "s %d %d %d %d %d %d %d",
			sct->ceil, sct->ceiltx, sct->floor, sct->floortx,
			sct->gravity, sct->roof, sct->type);
		w_vtx = sct->w_vtx_start;
		while (w_vtx)
		{
			dprintf(fd, " %d", w_vtx->vtx->id);
			w_vtx = w_vtx->next;
		}
		dprintf(fd, " :");
		w_vtx = sct->w_vtx_start;
		while (w_vtx)
		{
			dprintf(fd, " %d", w_vtx->ref);
			w_vtx = w_vtx->next;
		}
		dprintf(fd, "\n");
		sct = sct->next;
		i++;
	}

	// objects
	ft_putendl_fd("# object: x y sct ref iswpn", fd);
	obj = env->editor.objects;
	while (obj)
	{
		if (obj->dd != DD_NTTY && obj->dd != DD_SPEC)
			dprintf(fd, "o %d %d %d %d %d\n",
			(int)obj->pos.x, (int)obj->pos.y,
			obj->sct->id, obj->ref, obj->iswpn);
		obj = obj->next;
	}

	// entities
	ft_putendl_fd("# entity: x y sct ref", fd);
	obj = env->editor.objects;
	while (obj)
	{
		if (obj->dd == DD_NTTY)
			dprintf(fd, "e %d %d %d %d\n",
			(int)obj->pos.x, (int)obj->pos.y, obj->sct->id, obj->ref);
		obj = obj->next;
	
	}

	// player
	ft_putendl_fd("# player: x y angle sct", fd);
	obj = env->editor.objects;
	while (obj)
	{
		if (obj->dd == DD_SPEC)
		{
			dprintf(fd, "p %d %d %d %d\n",
			(int)obj->pos.x, (int)obj->pos.y, (int)obj->dir, obj->sct->id);
			break ;
		}
		obj = obj->next;
	}

	close(fd);
}
