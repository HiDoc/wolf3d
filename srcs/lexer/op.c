/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:21:42 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/06 18:03:46 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	is_spc(int c) { return c == ' '; }
int	is_tab(int c) { return c == '\t'; }
int	is_min(int c) { return c == '-'; }
int	is_end(int c) { return c == '\n'; }
int	is_sec(int c) { return c == 's'; }
int	is_vtx(int c) { return c == 'v'; }
int	is_plr(int c) { return c == 'p'; }
int	is_cmt(int c) { return c == '#'; }
int	is_dgt(int c) { return ft_isdigit(c); }

typedef struct s_op		t_op;

struct s_op
{
	unsigned	val;
	const char	*name;
	int			(*verify)(int);
};

t_op	op_tab[11] = {
	{
		{(1U << 0), "Space", ' ', &is_spc},
		{(1U << 1), "Tabulation", &is_tab},
		{(1U << 2), "Integer", &is_dig},
		{(1U << 3), "Minus", &is_min},
		{(1U << 4), "END", &is_end},
		{(1U << 5), "sector", &is_sec},
		{(1U << 6), "vertex", &is_vtx},
		{(1U << 7), "player", &is_plr},
		{(1U << 8), "error", NULL},
		{(1U << 9), "comment", &is_cmt},
		{(1U << 10), "none", NULL}
	};
}