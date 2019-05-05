/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:16:26 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/04 23:06:27 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		delete_object(t_object *obj, t_env *env)
{
	t_object	*ptr;

	ptr = env->editor.objects;
	if (ptr == obj)
	{
		if (obj->dd == DD_SPEC && obj->ref == 0)
		{
			env->editor.onespawn = 0;
			env->editor.spawn_set = 0;
			ft_bzero(&env->editor.spawn_pos, sizeof(t_pos));
			env->editor.spawn_dir = 0;
		}
		env->editor.objects = ptr->next;
		lt_release((void**)&obj->name);
		lt_release((void**)&obj);
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == obj)
		{
			if (obj->dd == DD_SPEC && obj->ref == 0)
			{
				env->editor.onespawn = 0;
				env->editor.spawn_set = 0;
				ft_bzero(&env->editor.spawn_pos, sizeof(t_pos));
				env->editor.spawn_dir = 0;
			}
			ptr->next = ptr->next->next;
			lt_release((void**)&obj->name);
			lt_release((void**)&obj);
		}
		ptr = ptr->next;
	}
}
