/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:10:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 02:37:52 by sgalasso         ###   ########.fr       */
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
	new->sct = env->editor.sct_hover;
	new->pos = env->mouse;
	if (!(env->objects))
	{
		env->objects = new;
		env->objects->next = 0;
	}
	else
	{
		new->next = env->objects;
		env->objects = new;
	}
}
