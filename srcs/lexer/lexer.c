/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:37:37 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 16:57:10 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

const t_op	op_first[12] = {
	{(1U << SECTOR), "Sector", &is_sec, 10},
	{(1U << VERTEX), "Vertex", &is_vtx, 2},
	{(1U << PLAYER), "Player", &is_plr, 4},
	{(1U << OBJECT), "Object", &is_obj, 5},
	{(1U << WOJECT), "Wall object", &is_wob, 3},
	{(1U << SPECIA), "Special", &is_spe, 3},
	{(1U << ENTITY), "Entity", &is_ent, 4},
	{(1U << COMMNT), "Comment", &is_cmt, 100},
	{(1U << TXTURE), "Texture", &is_txt, 3},
	{(1U << 9), "End", &is_end, 1},
	{(1U << 10), "None", NULL, 0},
	{(1U << 11), "Error", NULL, 0}
};

static unsigned	token_calc(t_parseline *line)
{
	t_token		*iter;
	unsigned	count;

	iter = line->first;
	count = 0;
	while (iter)
	{
		if (iter->type == (1U << 2) &&
			(iter->next && iter->next->type != (1U << 2)))
			count++;
		iter = iter->next;
	}
	return (count);
}

int		lexer_vertex(t_parseline *line)
{
	t_token		*iter;
	unsigned	number;

	number = 0;
	iter = line->first;
	if (!iter || !iter->next)
		return (0);
	while (iter)
	{
		if (iter->type == (1U << 2))
			number = number * 10 + (iter->value - '0');
		if (iter->type == (1U << 2) && (iter->next && iter->next->type != (1U << 2)))
		{
			if (number > 100)
				return (0);
			number = 0;
		}
		iter = iter->next;
	}
	return (1);
}

int	lexer(t_parsefile *file)
{
	t_parseline	*line;
	unsigned	iter;

	line = file->first;
	iter = 0;
	while (line)
	{
		while (iter < 10)
		{
			if (op_first[iter].val == line->first->type
				&& token_calc(line) > op_first[iter].max_token)
				{
					line->first->type = (1U << 11);
					return (0);
				}
			iter++;
		}
	}
	return (1);
}