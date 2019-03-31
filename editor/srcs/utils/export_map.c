/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:33:40 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/31 17:08:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        export_map(t_env *env)
{
	char	*path;
	int		fd;

	printf("%s\n", env->map_name);

	if (!(path = ft_strjoin("maps/", env->map_name)))
		ui_error_exit_sdl("Editor: Error while opening file", env->data);

	if ((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ui_error_exit_sdl("Editor: Error while opening file", env->data);
	free(path);	

	ft_putendl_fd("# map name", fd);
	ft_putendl_fd(env->map_name, fd);

	ft_putendl_fd("# nb vertex:", fd);
	ft_putnbr_fd(env->nb_vtx, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("# vertex: x y", fd);
	//

	ft_putendl_fd("# nb sectors:", fd);
	ft_putnbr_fd(env->nb_sct, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("# sector: ceil floor n-vertex n-neighbors", fd);
	//

	ft_putendl_fd("# nb wall objects:", fd);
	ft_putnbr_fd(env->nb_wall_objs, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("# wall_object: x y sector ref", fd);
	//

	ft_putendl_fd("# nb consumables:", fd);
	ft_putnbr_fd(env->nb_consumables, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("# consumable: x y sector ref is_wpn", fd);
	//
	
	ft_putendl_fd("# nb entities:", fd);
	ft_putnbr_fd(env->nb_entities, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("# entity: x y sector ref", fd);
	//

	ft_putendl_fd("# nb specials:", fd);
	ft_putnbr_fd(env->nb_specials, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("# special: x y ref", fd);
	//

	if (close(fd) == -1)
		ui_error_exit_sdl("Editor: Error while closing file", env->data);
}
