/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:31:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/07 18:47:44 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
int	is_spc(int c) { return c == ' '; }
int	is_tab(int c) { return c == '\t'; }
int	is_min(int c) { return c == '-'; }
int	is_end(int c) { return c == '\n'; }
int	is_sec(int c) { return c == 's'; }
int	is_vtx(int c) { return c == 'v'; }
int	is_obj(int c) { return c == 'o'; }
int	is_txt(int c) { return c == 't'; }
int	is_ent(int c) { return c == 'e'; }
int	is_wob(int c) { return c == 'w'; }
int	is_spe(int c) { return c == 'x'; }
int	is_plr(int c) { return c == 'p'; }
int	is_cmt(int c) { return c == '#'; }
int	is_dgt(int c) { return (c) >= '0' && (c) <= '9'; }

typedef struct s_op		t_op;

struct s_op
{
	unsigned	val;
	const char	*name;
	int			(*verify)(int);
};

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

const t_op	op_next[6] = {
	{(1U << 0), "Space", &is_spc},
	{(1U << 1), "Tabulation", &is_tab},
	{(1U << 2), "Integer", &is_dgt},
	{(1U << 3), "Minus", &is_min},
	{(1U << 4), "End", &is_end},
	{(1U << 5), "None", NULL}
};


const t_op	op_first[12] = {
	{(1U << SECTOR), "Sector", &is_sec},
	{(1U << VERTEX), "Vertex", &is_vtx},
	{(1U << PLAYER), "Player", &is_plr},
	{(1U << OBJECT), "Object", &is_obj},
	{(1U << WOJECT), "Wall object", &is_wob},
	{(1U << SPECIA), "Special", &is_spe},
	{(1U << ENTITY), "Entity", &is_ent},
	{(1U << COMMNT), "Comment", &is_cmt},
	{(1U << TXTURE), "Texture", &is_txt},
	{(1U << 9), "End", &is_end},
	{(1U << 10), "None", NULL},
	{(1U << 11), "Error", NULL}
};

t_token	*new_token(char c, unsigned pos)
{
	unsigned	iter;
	unsigned	maxiter;
	t_token		*new;
	t_op		*op;

	iter = 0;
	maxiter = pos ? 5 : 9;
	op = pos ? (t_op *)op_next : (t_op *)op_first;
	new = NULL;
	while (iter < maxiter)
	{
		if (op[iter].verify(c))
			break;
		iter++;
	}
	if ((new = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	new->next = NULL;
	new->type = op[iter].val;
	new->pos = pos;
	new->value = c;
	return (new);
}
