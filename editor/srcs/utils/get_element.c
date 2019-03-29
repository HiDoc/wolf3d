/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:58:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 16:13:57 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_elem		*get_element(int id, t_env *env)
{
	t_elem		*current;

	current = env->elements;
	while (current)
	{
		if (current->id == id)
			return (current);
		current = current->next;
	}
	return (0);
}
