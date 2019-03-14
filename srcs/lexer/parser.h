#ifndef PARSER_H
# define PARSER_H

#include "doom.h"
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

const t_op op[3] = {
	{TOK_VTX, TOK_NVTX, TOK_INT, 2},
	{TOK_SEC, TOK_NSEC, TOK_MIN | TOK_INT, 20},
	{TOK_PLR, TOK_NPLR, TOK_INT, 4}
};

int (*get_token[8])(int) = {
	&is_spc,
	&is_tab,
	&ft_isdigit,
	&is_min,
	&is_end,
	&is_sec,
	&is_vtx,
	&is_plr
};

#endif
