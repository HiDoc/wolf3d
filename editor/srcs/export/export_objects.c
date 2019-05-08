/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:59:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 18:00:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		export_entity(int fd, t_pos min, t_env *env)
{
	t_object	*obj;

	ft_putendl_fd("# entity: x y sct ref", fd);
	obj = env->editor.objects;
	while (obj)
	{
		if (obj->dd == DD_NTTY)
		{
			ft_putstr_fd("e ", fd);
			ft_putnbr_fd((int)(obj->pos.x - min.x), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd((int)(obj->pos.y - min.y), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(obj->sct->id, fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(obj->ref, fd);
			ft_putchar_fd('\n', fd);
		}
		obj = obj->next;
	}
}

static void		export_player(int fd, t_pos min, t_env *env)
{
	t_object	*obj;

	ft_putendl_fd("# player: x y angle sct", fd);
	obj = env->editor.objects;
	while (obj)
	{
		if (obj->dd == DD_SPEC)
		{
			ft_putstr_fd("p ", fd);
			ft_putnbr_fd((int)(obj->pos.x - min.x), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd((int)(obj->pos.y - min.y), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd((int)(obj->dir * 180 / M_PI), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(obj->sct->id, fd);
			ft_putchar_fd('\n', fd);
			break ;
		}
		obj = obj->next;
	}
}

void			export_objects(int fd, t_pos min, t_env *env)
{
	t_object	*obj;

	ft_putendl_fd("# object: x y sct ref iswpn", fd);
	obj = env->editor.objects;
	while (obj)
	{
		if (obj->dd != DD_NTTY && obj->dd != DD_SPEC)
		{
			ft_putstr_fd("o ", fd);
			ft_putnbr_fd((int)(obj->pos.x - min.x), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd((int)(obj->pos.y - min.y), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(obj->sct->id, fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(obj->ref, fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(obj->iswpn, fd);
			ft_putchar_fd('\n', fd);
		}
		obj = obj->next;
	}
	export_entity(fd, min, env);
	export_player(fd, min, env);
}
