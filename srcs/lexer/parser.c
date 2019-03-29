/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/28 16:32:08 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const t_op op[3] = {
	{TOK_VTX, TOK_NVTX, TOK_INT, 2},
	{TOK_SEC, TOK_NSEC, TOK_MIN | TOK_INT, 20},
	{TOK_PLR, TOK_NPLR, TOK_INT, 4}
};

int	lexer_vertex(t_token *iter)
{
	unsigned	number;

	number = 0;
	while (iter)
	{
		if ((iter->type & op[0].values))
		{
			if (number == op[0].max_valid)
			{
				iter->type = TOK_ERR;
				return (0);
			}
			while (iter && iter->type == TOK_INT)
				iter = iter->next;
			number++;
		}
		else if (iter->type != TOK_SPC
			&& iter->type != TOK_TAB
			&& iter->type != TOK_END)
		{
			iter->type = TOK_ERR;
			return (0);
		}
		else iter = iter->next;
	}
	return (number == 2);
}

int	lexer(t_parseline *line)
{
	t_token		*iter;

	iter = line->first;
	if (iter->type == TOK_VTX)
	{
		iter = iter->next;
		if (!lexer_vertex(iter))
			return (0);
	}
	return (1);
}

void	print_err(t_parseline *line)
{
	t_token	*iter;

	iter = line->first;
	printf("\033[31mparsing error\033[0m at line %d:\n", line->nline);
	while (iter)
	{
		printf("%c", iter->value);
		iter = iter->next;
	}
	iter = line->first;
	while (iter)
	{
		if (iter->type == TOK_ERR)
		{
			printf("\033[31m^\n\033[0m");
			printf("Unexpected token %s\n", iter->name);
			printf("Vertex must only contain two integers\n");
			break ;
		}
		else if (iter->type == TOK_SPC && iter->type == TOK_TAB)
			printf("%c", iter->value);
		else
			printf(" ");
		iter = iter->next;
	}
}

int	reader(int fd, t_parsefile *file, unsigned *nvertex, unsigned *nsector)
{
	t_parseline	*line;
	t_token		*iter;
	const int	nread = 1;
	unsigned	pos;
	unsigned	nline;
	char		buffer[nread + 1];

	line = file->first;
	pos = 0;
	nline = 0;
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
				pos = 0;
			}
		}
		else
		{
			iter->next = new_token(*buffer, pos);
			iter = iter->next;
			if (iter->type == TOK_END)
			{
				nline++;
				if (!lexer(line))
				{
					print_err(line);
					return (0);
				}
				line->next = new_line(nline);
				line = line->next;
				pos = 0;
			}
			else pos++;
		}
		if (iter->type == TOK_VTX)
			(*nvertex)++;
		if (iter->type == TOK_SEC)
			(*nsector)++;
	}
	return (1);
}

int	printer(t_parsefile *file)
{
	t_parseline	*line;
	t_token	*iter;

	line = file->first;
	while (line)
	{
		iter = line->first;
		// printf("[%u] ", line->nline);
		while (iter)
		{
			if (iter->type != TOK_SPC && iter->type != TOK_TAB && iter->type != TOK_END)
		;//		printf("[%u][%s %c] ", iter->pos, iter->name, iter->value);
			if (iter->type == TOK_END)
		;//		printf("\n");
			line->first = iter;
			iter = iter->next;
			free(line->first);
		}
		file->first = line;
		line = line->next;
		if (file->first)
			free(file->first);
	}
	return (1);
}

int	parser(t_engine *eng, char *filename)
{
	int		fd;
	t_parsefile	file;
	unsigned	nvertex;
	unsigned	nsector;

	(void)eng;
	file.first = new_line(0);
	nvertex = 0;
	nsector = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	reader(fd, &file, &nvertex, &nsector);
	printer(&file);
	printf("\n");
	printf("vertexes: %u\n", nvertex);
	printf("sectors: %u\n", nsector);
	return (1);
}

int main(int argc, char **argv)
{
	t_engine e;

	if (argc > 1)
	{
		if (argv[1])
			parser(&e, argv[1]);
	}
	return (0);
}
