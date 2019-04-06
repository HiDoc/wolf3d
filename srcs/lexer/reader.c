/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:09:19 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/06 16:45:09 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	set_new_line(t_parseline *line, unsigned *nline, unsigned *pos)
{
	(*pos) = 0;
	(*nline)++;
	if (!lexer(line))
	{
		print_err(line);
		return (0);
	}
	line->next = new_line(nline);
	line = line->next;
	return (1);
}

int			reader(int fd, t_parsefile *file, unsigned *nvtx, unsigned *nsct)
{
	t_parseline	*line;
	t_token		*iter;
	unsigned	pos;
	unsigned	nline;
	char		buffer[2];

	line = file->first;
	nline = 0;
	pos = 0;
	while (read(fd, buffer, 1) > 0)
	{
		if (line->first == NULL)
		{
			line->first = new_token(*buffer, pos);
			iter = line->first;
		}
		else
		{
			iter->next = new_token(*buffer, pos);
			iter = iter->next;
			pos++;
		}
		if (iter->type == TOK_END) && !set_new_line(line, &nline, &pos)
			return (0);
		if (iter->type == TOK_VTX)
			(*nvertex)++;
		if (iter->type == TOK_SEC)
			(*nsector)++;
	}
	return (1);
}