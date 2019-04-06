/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:31:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/06 16:43:20 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_parseline *new_line(unsigned nline)
{
	t_parseline	*new;

	if ((new = (t_parseline *)malloc(sizeof(t_parseline))) == NULL)
		return (NULL);
	new->first = NULL;
	new->next = NULL;
	new->len = 0;
	new->nline = nline;
	return (new);
}

t_token	*new_token(char c, unsigned pos)
{
	unsigned	iter;
	t_token		*new;

	iter = 0;
	new = NULL;
	while (iter < 10)
	{
		if (op_tab[iter].verify(c))
			break;
		iter++;
	}
	if ((new = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	new->next = NULL;
	new->name = op_tab[iter].name;
	new->type = op_tab[iter].val;
	new->pos = pos;
	new->value = c;
	return (new);
}
