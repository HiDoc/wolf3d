/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:31:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 17:35:31 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned	token_count_until(t_token *start, unsigned type, unsigned until)
{
	unsigned	count;
	t_token		*iter;

	count = 0;
	iter = start;
	while (iter)
	{
		if (iter->type == (1U << until))
			break;
		if (iter->type == (1U << type) &&
			(iter->next && iter->next->type != (1U << type)))
			count++;
		iter = iter->next;
	}
	return (count);
}

unsigned	token_count(t_parseline *line, unsigned type)
{
	t_token		*iter;
	unsigned	count;

	iter = line->first;
	count = 0;
	while (iter)
	{
		if (iter->type == (1U << type) &&
			(iter->next && iter->next->type != (1U << type)))
			count++;
		iter = iter->next;
	}
	return (count);
}

int		verify_token_next(int iter, char c, unsigned which)
{
	const t_op	op_next[TOKEN_NEXT_MAX] = {
		{(1U << SPACE), "Space", &is_spc, 1},
		{(1U << TAB), "Tabulation", &is_tab, 1},
		{(1U << INT), "Integer", &is_dgt, 1},
		{(1U << MINUS), "Minus", &is_min, 1},
		{(1U << POINT), "Point", &is_ptn, 1},
		{(1U << NEND), "End", &is_end, 1},
		{(1U << NNONE), "None", NULL, 1}};

	if (which == TOKEN_VERIF)
		return (op_next[iter].verify(c));
	else
		return (op_next[iter].val);
}

int		verify_token_first(int iter, char c, unsigned which)
{
	const t_op	op_first[TOKEN_FRST_MAX] = {
		{(1U << SECTOR), "Sector", &is_sec, 10},
		{(1U << VERTEX), "Vertex", &is_vtx, 2},
		{(1U << PLAYER), "Player", &is_plr, 4},
		{(1U << OBJECT), "Object", &is_obj, 5},
		{(1U << SKYBOX), "Skybox Texture", &is_sky, 3},
		{(1U << ENTITY), "Entity", &is_ent, 4},
		{(1U << COMMNT), "Comment", &is_cmt, 100},
		{(1U << TXTURE), "Texture", &is_txt, 3},
		{(1U << MUSIC), "Music", &is_mus, 3},
		{(1U << END), "End", &is_end, 1},
		{(1U << NONE), "None", &no_op_int, 0},
		{(1U << ERROR), "Error", &no_op_int, 0}};

	if (which == TOKEN_VERIF)
		return (op_first[iter].verify(c));
	else
		return (op_first[iter].val);
}

t_token	*new_token(char c, unsigned pos)
{
	unsigned	iter;
	unsigned	maxiter;
	t_token		*new;
	int			(*funct)(int, char, unsigned);

	iter = 0;
	maxiter = pos ? TOKEN_NEXT_MAX - 1: TOKEN_FRST_MAX - 1;
	funct = pos ? &verify_token_next : &verify_token_first;
	new = NULL;
	while (iter < maxiter)
	{
		if (funct(iter, c, TOKEN_VERIF))
			break ;
		iter++;
	}
	new = ft_memalloc(sizeof(t_token));
	new->next = NULL;
	new->type = funct(iter, c, TOKEN_VALUE);
	new->pos = pos;
	new->value = c;
	return (new);
}
