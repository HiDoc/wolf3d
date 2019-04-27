/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:37:37 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 14:58:34 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	is_end(int c) { return c == '\n'; }
static int	is_sec(int c) { return c == 's'; }
static int	is_vtx(int c) { return c == 'v'; }
static int	is_obj(int c) { return c == 'o'; }
static int	is_txt(int c) { return c == 't'; }
static int	is_ent(int c) { return c == 'e'; }
static int	is_wob(int c) { return c == 'w'; }
static int	is_spe(int c) { return c == 'x'; }
static int	is_plr(int c) { return c == 'p'; }
static int	is_cmt(int c) { return c == '#'; }

typedef struct s_op
{
	unsigned	val;
	const char	*name;
	int			(*verify)(int);
	unsigned	max_token;
}t_op;

enum e_op_first{
	SECTOR,
	VERTEX,
	PLAYER,
	OBJECT,
	WOJECT,
	SPECIA,
	ENTITY,
	COMMNT,
	TXTURE
};

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