#include "doom.h"

typedef struct s_parsefile	t_parsefile;
typedef struct s_parseline	t_parseline;
typedef struct s_token		t_token;

struct	s_token
{
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

#define TOK_SPC		0x1
#define TOK_NSPC	"space"
#define	TOK_TAB		0x2
#define TOK_NTAB	"tab"
#define TOK_INT		0x3
#define TOK_NINT	"INT"
#define TOK_MIN		0x4
#define TOK_NMIN	"MINUS"
#define	TOK_END		0x5
#define	TOK_NEND	"END"
#define	TOK_SEC		0x6
#define	TOK_NSEC	"sector"
#define	TOK_VTX		0x7
#define	TOK_NVTX	"vertex"
#define	TOK_PLR		0x8
#define	TOK_NPLR	"player"
#define	TOK_NONE	"none"

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
	int		type;
	t_token		*new;

	type = -1;
	(c == ' ') ? type = TOK_SPC : 0;
	(c == '\t') ? type = TOK_TAB : 0;
 	(ft_isdigit(c)) ? type = TOK_INT : 0;
 	(c == '-') ? type = TOK_MIN : 0;
	(c == '\n') ? type = TOK_END : 0;
	(c == 's') ? type = TOK_SEC : 0;
	(c == 'v') ? type = TOK_VTX : 0;
	(c == 'p') ? type = TOK_PLR : 0;
	if ((new = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	new->name = TOK_NONE;
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
	new->type = type;	
	return (new);
}

int	parser(t_engine *eng, char *filename)
{
	int		fd;
	unsigned	nline;
	unsigned	pos;
	const int	nread = 1;
	t_parsefile	file;
	t_parseline	*line;
	t_token		*iter;
	unsigned	nvertex;
	unsigned	nsector;
	char		buffer[nread + 1];

	(void)eng;
	(void)file;
	file.first = NULL;
	buffer[1] = '\0';
	nline = 0;
	nvertex = 0;
	nsector = 0;
	pos = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	file.first = new_line(nline);
	line = file.first;
	while (read(fd, buffer, nread) > 0)
	{
		if (line->first == NULL)
		{
			line->first = new_token(*buffer, pos);
			iter = line->first;
			if (iter->type == TOK_END)
			{
				nline++;
				line->next = new_line(nline);
				line = line->next;
			}
		}
		else
		{
			iter->next = new_token(*buffer, pos);
			iter = iter->next;
			if (iter->type == TOK_END)
			{
				nline++;
				line->next = new_line(nline);
				line = line->next;
			}
		}
		if (iter->type == TOK_VTX)
			nvertex++;
		if (iter->type == TOK_SEC)
			nsector++;
	}
	line = file.first;
	while (line)
	{
		iter = line->first;
		printf("[%u] ", line->nline);
		while (iter)
		{
			if (iter->type != TOK_SPC && iter->type != TOK_TAB)
				printf("[%s] ", iter->name);
			if (iter->type == TOK_END)
				printf("\n");
			line->first = iter;
			iter = iter->next;
			free(line->first);
		}
		file.first = line;
		line = line->next;
		if (file.first)
			free(file.first);
	}
	printf("return\n");
	return (1);
}

int main(int argc, char **argv)
{
	t_engine e;
	if (argc > 1)
	{	
		parser(&e, argv[1]);
	}
	return (0);
}
