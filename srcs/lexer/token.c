/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:31:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 12:27:22 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		verify_token_next(int iter, char c, unsigned which)
{
	const t_op	op_next[6] = {
		{(1U << 0), "Space", &is_spc, 1},
		{(1U << 1), "Tabulation", &is_tab, 1},
		{(1U << 2), "Integer", &is_dgt, 1},
		{(1U << 3), "Minus", &is_min, 1},
		{(1U << 4), "End", &is_end, 1},
		{(1U << 5), "None", NULL, 1}};

	if (which == TOKEN_VERIF)
		return (op_next[iter].verify(c));
	else
		return (op_next[iter].val);
}

int		verify_token_first(int iter, char c, unsigned which)
{
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
		{(1U << 11), "Error", NULL, 0}};

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
	maxiter = pos ? 5 : 9;
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
