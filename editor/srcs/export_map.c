/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:33:40 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/07 20:01:36 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        export_map(t_env *env)
{
	char	*path;
	int		fd;
	int		i;

	if (!(path = ft_strjoin("maps/", env->map_name)))
		ui_error_exit_sdl("Editor: Error while opening file", env->data);
	if ((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ui_error_exit_sdl("Editor: Error while opening file", env->data);
	free(path);
		
	ft_putendl_fd("# wall vertex (x y)", fd);
	i = 0;
	while (i < env->vrx_index)
	{
		ft_putstr_fd("v ", fd);
		ft_putnbr_fd(env->vertex[i].pos.x, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(env->vertex[i].pos.y, fd);
		ft_putstr_fd("\n\n", fd);
		i++;
	}
	ft_putendl_fd("# object vertex (x y)", fd);
	//
	ft_putendl_fd("# monster vertex (x y)", fd);
	//
	ft_putendl_fd("# objects (vertex sector indexobject)", fd);
	//
	ft_putendl_fd("# sector (floor ceil indexVertex, neighbours", fd);
	i = 0;
	while (i < env->sct_index)
	{
		ft_putstr_fd("s 0", fd);
		//ft_putnbr_fd(env->vertex[i].pos.x, fd);
		ft_putstr_fd(" 20", fd);
		//ft_putnbr_fd(env->vertex[i].pos.y, fd);
		ft_putchar_fd(' ', fd);
		/*while ()
		{
		
		}
		while ()
		{
		
		}*/

		ft_putstr_fd("\n\n", fd);
		i++;
	}
	ft_putendl_fd("# monster (vertex sector indexMonster)", fd);
	//
	ft_putendl_fd("# texture (vertex1 vertex2 indexTexture)", fd);
	//
	ft_putendl_fd("# player (x y angle sector)", fd);
	//
	if (close(fd) == -1)
		ui_error_exit_sdl("Editor: Error while closing file", env->data);
}
