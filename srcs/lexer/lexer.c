/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:37:37 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/06 16:38:59 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	lexer_vertex(t_token *iter)
{
	unsigned	number;

	number = 0;
	(void)iter;
	(void)number;
	return (1);
}

int	lexer(t_parseline *line)
{
	t_token		*iter;

	iter = line->first;
	if (iter->type == TOK_VTX)
	{
		iter = iter->next;
		if (!lexer_vertex(iter))
			return (0);
	}
	return (1);
}