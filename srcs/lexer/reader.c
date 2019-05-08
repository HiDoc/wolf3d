/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:09:19 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 19:39:24 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_parseline		*set_new_line(unsigned *nline, unsigned *pos)
{
	(*pos) = 0;
	(*nline)++;
	return (new_line(*nline, 0));
}

void	set_absolute(t_parsefile *file, t_parseline *line, t_token *iter)
{
	if (iter->type == SECTOR)
		line->absolute = file->nsector++;
	if (iter->type == VERTEX)
		line->absolute = file->nvertex++;
}

int		reader(int fd, t_parsefile *file)
{
	char		buffer[2];
	t_parseline	*line;
	t_token		*iter;

	line = file->first;
	while (read(fd, buffer, 1) > 0)
	{
		if (line->first == NULL)
		{
			line->first = new_token(*buffer, file->pos++);
			set_absolute(file, line, (iter = line->first));
		}
		else
		{
			iter->next = new_token(*buffer, file->pos++);
			iter = iter->next;
		}
		if (iter->value == '\n')
		{
			line->next = set_new_line(&file->nline, &file->pos);
			line = line->next;
		}
	}
	if (!line->first)
		line->first = new_token('\n', file->pos);
	return (1);
}
