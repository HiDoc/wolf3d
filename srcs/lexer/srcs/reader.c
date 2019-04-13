/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:09:19 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/13 18:19:23 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int		set_new_line(t_parseline **line, unsigned *nline, unsigned *pos)
{
	(*pos) = 0;
	(*nline)++;
	(*line)->next = new_line(*nline);
	(*line) = (*line)->next;
	return (1);
}

int		read_new_line(char *buffer, t_parsefile *file)
{
	return (1);
}

int		reader(int fd, t_parsefile *file, unsigned *nvtx, unsigned *nsct)
{
	char		buffer[2];
	t_parseline	*line;
	t_token		*iter;
	unsigned	nline;
	unsigned	pos;

	line = file->first;
	nline = 0;
	pos = 0;
	while (read(fd, buffer, 1) > 0)
	{
		if (line->first == NULL)
		{
			line->first = new_token(*buffer, pos);
			iter = line->first;
			pos++;
		}
		else
		{
			iter->next = new_token(*buffer, pos);
			iter = iter->next;
			pos++;
		}
		if (iter->value == '\n')
			set_new_line(&line, &nline, &pos);
		if (iter->value == 'v')
			(*nvtx)++;
		if (iter->value == 's')
			(*nsct)++;
	}
	return (1);
}