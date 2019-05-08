/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:44:12 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 16:49:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		export_vertex(int fd, t_pos min, t_env *env)
{
	t_vtx		*vtx;
	int			i;

	ft_putendl_fd("# vertex: x y", fd);
	i = 0;
	vtx = env->editor.vertex;
	while (vtx)
	{
		vtx->id = i;
		ft_putstr_fd("v ", fd);
		ft_putnbr_fd((int)(vtx->pos.x - min.x), fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd((int)(vtx->pos.y - min.y), fd);
		ft_putchar_fd('\n', fd);
		vtx = vtx->next;
		i++;
	}
}
