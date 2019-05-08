/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:09:19 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 16:55:53 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		set_new_line(t_parseline **line, unsigned *nline, unsigned *pos)
{
	(*pos) = 0;
	(*nline)++;
	(*line)->next = new_line(*nline, 0);
	(*line) = (*line)->next;
	return (1);
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
			iter = line->first;
			if (iter->type == SECTOR || iter->type == VERTEX)
				line->absolute = (iter->type == SECTOR
				? file->nsector++ : file->nvertex++);
		}
		else
		{
			iter->next = new_token(*buffer, file->pos++);
			iter = iter->next;
		}
		if (iter->value == '\n')
			set_new_line(&line, &file->nline, &file->pos);
	}
	if (!line->first)
		line->first = new_token('\n', file->pos);
	return (1);
}