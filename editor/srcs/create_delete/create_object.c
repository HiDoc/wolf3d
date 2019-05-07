/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:10:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 21:03:43 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		create_object(t_elem *element, t_env *env)
{
	t_object	*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_object)), ft_memdel)))
		ui_error_exit_sdl("Editor: create object, out of memory");
	new->ref = element->ref;
	new->dd = element->dd;
	if (!(new->name = lt_push(ft_strdup(element->str), ft_memdel)))
		ui_error_exit_sdl("Editor: create object, out of memory");
	new->pos = env->mouse;
	if (element->dd == DD_NTTY)
		new->color = C_RED;
	else if (element->dd == DD_CONS)
		new->color = C_GREEN;
	else
		new->color = C_WHITE;
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
