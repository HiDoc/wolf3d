/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:16:26 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 02:40:21 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		delete_object(t_object *obj, t_env *env)
{
	t_object	*ptr;

	ptr = env->objects;
	if (ptr == obj)
	{
		env->objects = ptr->next;
		lt_release(obj->name);
		lt_release(obj);
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == obj)
		{
			ptr->next = ptr->next->next;
			lt_release(obj->name);
			lt_release(obj);
		}
		ptr = ptr->next;
	}
}
