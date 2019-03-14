#include "parser.h"

t_parseline *new_line(unsigned nline)
{
	t_parseline	*new;

	if ((new = (t_parseline *)malloc(sizeof(t_parseline))) == NULL)
		return (NULL);
	new->first = NULL;
	new->next = NULL;
	new->len = 0;
	new->nline = nline;
	return (new);
}

t_token	*new_token(char c, unsigned pos)
{
	unsigned	iter;
	t_token		*new;

	iter = 0;
	new = NULL;
	while (iter < 8)
	{
		if (get_token[iter](c))
			break;
		iter++;
	}
	if ((new = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	new->name = TOK_NONE;
	new->type = (1 << iter);
	(c == ' ') ? new->name = TOK_NSPC : 0;
	(c == '\t') ? new->name = TOK_NTAB : 0;
 	(ft_isdigit(c)) ? new->name = TOK_NINT : 0;
 	(c == '-') ? new->name = TOK_NMIN : 0;
	(c == '\n') ? new->name = TOK_NEND : 0;
	(c == 's') ? new->name = TOK_NSEC : 0;
	(c == 'v') ? new->name = TOK_NVTX : 0;
	(c == 'p') ? new->name = TOK_NPLR : 0;
	new->next = NULL;
	new->pos = pos;
	new->value = c;	
	return (new);
}

