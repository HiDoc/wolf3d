/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:02 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/28 16:36:30 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#define TOK_SPC		(1U << 0)
#define TOK_NSPC	"space"
#define	TOK_TAB		(1U << 1)
#define TOK_NTAB	"tab"
#define TOK_INT		(1U << 2)
#define TOK_NINT	"INT"
#define TOK_MIN		(1U << 3)
#define TOK_NMIN	"MINUS"
#define	TOK_END		(1U << 4)
#define	TOK_NEND	"END"
#define	TOK_SEC		(1U << 5)
#define	TOK_NSEC	"sector"
#define	TOK_VTX		(1U << 6)
#define	TOK_NVTX	"vertex"
#define	TOK_PLR		(1U << 7)
#define	TOK_NPLR	"player"
#define	TOK_ERR		(1U << 8)
#define	TOK_NERR	"error"
#define	TOK_COM		(1U << 9)
#define	TOK_NCOM	"comment"
#define	TOK_NONE	"none"

typedef struct s_parsefile	t_parsefile;
typedef struct s_parseline	t_parseline;
typedef struct s_token		t_token;
typedef struct s_op		t_op;

struct	s_token
{
	int		value;
	unsigned	type;
	unsigned	pos;
	const char	*name;
	t_token		*next;
};

struct	s_parseline
{
	t_token		*first;
	t_parseline	*next;
	unsigned	len;
	unsigned	nline;
};

struct	s_parsefile
{
	int		nvertex;
	int		nsector;
	t_parseline	*first;
};

struct	s_op
{
	unsigned	type;
	const char	*name;
	unsigned	values;
	unsigned	max_valid;
};

int	is_spc(int c);
int	is_tab(int c);
int	is_min(int c);
int	is_end(int c);
int	is_sec(int c);
int	is_vtx(int c);
int	is_plr(int c);

t_token	*new_token(char c, unsigned pos);
t_parseline *new_line(unsigned nline);

#endif
