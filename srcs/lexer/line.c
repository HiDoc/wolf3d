/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:37:18 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 22:06:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_parseline	*new_line(unsigned nline, unsigned absolute)
{
	t_parseline	*new;

	if ((new = (t_parseline *)ft_memalloc(sizeof(t_parseline))) == NULL)
		return (NULL);
	new->first = NULL;
	new->next = NULL;
	new->nline = nline;
	new->absolute = absolute;
	new->len = 0;
	return (new);
}
