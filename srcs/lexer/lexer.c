/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:37:37 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 17:52:24 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	lexer_sector_points(t_token *iter)
{
	unsigned count;

	count = 0;
	while (iter && iter->type != POINT)
	{
		if (iter->type == INT)
		{
			if (iter->next && iter->next->type != INT)
				count++;
		}
		iter = iter->next;
	}
	return (count);
}

int		lexer_sector(t_parseline *line, int max, int current)
{
	t_token		*iter;
	unsigned	nvtx;
	unsigned	ntxt;

	nvtx = 0;
	ntxt = 0;
	if (max < current)
		return (0);
	iter = line->first;
	while (iter && iter->type != POINT)
		iter = iter->next;
	iter = iter->next ? iter->next : NULL;
	nvtx = lexer_sector_points(iter);
	iter = iter->next ? iter->next : NULL;
	ntxt = lexer_sector_points(iter);
	return (ntxt == nvtx);
}

int		lexer_line(t_parseline *line)
{
	int			max;
	int			current;
	t_token		*iter;

	if (!line || !line->first)
		return (0);
	iter = line->first;
	current = token_count(line, INT);
	max = verify_token_first(iter->type, 0, TOKEN_VERIF_MAX);
	if (iter->type == END || iter->type == COMMNT)
		return (1);
	if (iter->type == SECTOR)
		return (lexer_sector(line, max, current));
	printf("%d %d\n", token_count(line, NNONE), line->nline);
	return (max == current && !token_count(line, NNONE));
}

int		lexer(t_parsefile *file)
{
	t_parseline	*line;

	line = file->first;
	while (line)
	{
		if (!lexer_line(line))
			return (0);
		line = line->next;
	}
	return (1);
}