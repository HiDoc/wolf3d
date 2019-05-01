/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:10:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/01 13:52:09 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		create_object(t_elem *element, t_env *env)
{
	t_object   *new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_object)), ft_memdel)))
		ui_error_exit_sdl("Editor: create object, out of memory");
	new->ref = element->ref;
	new->category = element->type;
	if (!(new->name = lt_push(ft_strdup(element->str), ft_memdel)))
		ui_error_exit_sdl("Editor: create object, out of memory");
	new->pos = env->mouse;
	if (!(env->editor.objects))
	{
		env->editor.objects = new;
		env->editor.objects->next = 0;
	}
	else
	{
		new->next = env->editor.objects;
		env->editor.objects = new;
	}
}
