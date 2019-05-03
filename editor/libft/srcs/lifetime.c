/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:01:58 by tblaudez          #+#    #+#             */
/*   Updated: 2019/05/03 15:03:29 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lt	*get_lifetime(t_lt *new_ptr)
{
	static t_lt	*lifetime = 0;

	if (new_ptr)
		lifetime = new_ptr;
	return (lifetime);
}

void	*lt_push(void *ptr, void (*f)(void **))
{
	t_lt	*lifetime;

	if (!(lifetime = (t_lt *)(malloc(sizeof(t_lt)))))
		return (0);
	lifetime->ptr = ptr;
	lifetime->f = f;
	lifetime->next = get_lifetime(0);
	get_lifetime(lifetime);
	return (ptr);
}

void	lt_release(void **ptr)
{
	t_lt	*lifetime;
	t_lt	*tmp;

	lifetime = get_lifetime(0);
	if (lifetime->ptr == *ptr)
	{
		get_lifetime(lifetime->next);
		if (lifetime->ptr)
			(*(lifetime->f))(ptr);
		ft_memdel((void**)&lifetime);
		return ;
	}
	while (lifetime && lifetime->ptr != *ptr)
		lifetime = lifetime->next;
	if (!lifetime)
		return ;
	tmp = get_lifetime(0);
	while (tmp->next != lifetime)
		tmp = tmp->next;
	tmp->next = lifetime->next;
	if (lifetime->ptr)
		(*(lifetime->f))(ptr);
	ft_memdel((void**)&lifetime);
}

void	lt_destroy(void)
{
	t_lt	*lifetime;
	t_lt	*tmp;

	lifetime = get_lifetime(0);
	while (lifetime)
	{
		tmp = lifetime;
		lifetime = lifetime->next;
		(*(tmp->f))((void **)&(tmp->ptr));
		ft_memdel((void **)&tmp);
	}
}
