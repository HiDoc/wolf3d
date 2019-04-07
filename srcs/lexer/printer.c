/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:39:10 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/06 16:40:31 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	print_line(t_parseline *line)
{
	t_token	*iter;

	iter = line->first;
	printf("\033[31mparsing error\033[0m at line %d:\n", line->nline);
	while (iter)
	{
		printf("%c", iter->value);
		iter = iter->next;
	}
	iter = line->first;
	while (iter)
	{
		if (iter->type == TOK_ERR)
		{
			printf("\033[31m^\n\033[0m");
			printf("Unexpected token %s\n", iter->name);
			printf("Vertex must only contain two integers\n");
			break ;
		}
		else if (iter->type == TOK_SPC && iter->type == TOK_TAB)
			printf("%c", iter->value);
		else
			printf(" ");
		iter = iter->next;
	}
}

int	free_file(t_parsefile *file)
{
	t_parseline	*line;
	t_token	*iter;

	line = file->first;
	while (line)
	{
		iter = line->first;
		while (iter)
		{
			line->first = iter;
			iter = iter->next;
			free(line->first);
		}
		file->first = line;
		line = line->next;
		if (file->first)
			free(file->first);
	}
	return (1);
}