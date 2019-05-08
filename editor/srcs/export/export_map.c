/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:33:40 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 16:57:03 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		export_meta(int fd, t_env *env)
{
	ft_putendl_fd("# map name", fd);
	ft_putendl_fd(env->map_name, fd);
	ft_putendl_fd("# background music", fd);
	ft_putstr_fd("m ", fd);
	ft_putnbr_fd(env->editor.dropdown[DD_BGAUDIO].current->ref, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("# skybox texture", fd);
	ft_putstr_fd("b ", fd);
	ft_putnbr_fd(env->editor.dropdown[DD_SBTX].current->ref, fd);
	ft_putchar_fd('\n', fd);
}

void			export_map(t_env *env)
{
	t_vtx		*vtx;
	t_pos		min;
	char		*path;
	int			fd;

	ft_bzero(&min, sizeof(t_pos));
	if (!(path = lt_push(ft_strjoin("maps/", env->map_name), ft_memdel)))
		ui_error_exit_sdl("Editor: Error while opening file");
	if ((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ui_error_exit_sdl("Editor: Error while opening file");
	lt_release((void**)&path);
	vtx = env->editor.vertex;
	while (vtx)
	{
		(vtx->pos.x < min.x) ? min.x = vtx->pos.x : 0;
		(vtx->pos.y < min.y) ? min.y = vtx->pos.y : 0;
		vtx = vtx->next;
	}
	export_meta(fd, env);
	export_vertex(fd, min, env);
	export_sectors(fd, env);
	export_objects(fd, min, env);
	close(fd);
}
