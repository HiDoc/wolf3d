/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/13 20:35:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void 	retrieve_vertex(t_parseline *line, t_vtx *vtx)
{
	t_token		*iter;
	float		x;
	float		y;
	float		*ptr;

	iter = line->first;
	x = 0;
	y = 0;
	ptr = &x;
	while (iter)
	{
		if (iter->type == (1U << 2))
		{
			*ptr = (*ptr * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != (1U << 2))
				ptr = &y;
		}
		iter = iter->next;
	}
	vtx->x = x;
	vtx->y = y;
}

unsigned	token_calc(t_parseline *line)
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

void 	retrieve_sector(t_sector *sect, t_parseline *line, t_vtx *vtx)
{
	t_token		*iter;
	unsigned	count;
	unsigned	pos;

	sect->npoints = token_calc(line) - 2;
	sect->vertex = malloc(sizeof(t_vtx) * (sect->npoints + 1));

	iter = line->first;
	count = 0;
	pos = 0;
	while (iter)
	{
		if (iter->type == (1U << 2))
		{
			if (!count)
				sect->floor = sect->floor * 10 + (iter->value - '0');
			else if (count == 1)
				sect->ceil = sect->ceil * 10 + (iter->value - '0');
			else if (count > 1)
				pos = pos * 10 + (iter->value - '0');
		}
		if (iter->type == (1U << 2) && (iter->next
			&& iter->next->type != (1U << 2)))
		{
			if (count > 1)
			{
				sect->vertex[count - 2] = (t_vtx){vtx[pos].x, vtx[pos].y};
				printf("%.0f %.0f\n", sect->vertex[count - 2].x, sect->vertex[count - 2].y);
			}
			count++;
			pos = 0;
		}
		iter = iter->next;
	}
	if (count > 1)
		sect->vertex[count - 2] = (t_vtx){sect->vertex[0].x, sect->vertex[0].y};
}

void	load_vertex(t_parsefile *file, t_vtx *vert)
{
	t_parseline	*line;
	t_token		*iter;
	unsigned	pos;

	line = file->first;
	pos = 0;
	while (line)
	{
		if (line->first)
		{
			if (line->first->type == (1U << 1))
			{
				retrieve_vertex(line, &vert[pos]);
				printf("v %.0f %.0f \n", vert[pos].x, vert[pos].y);
				pos++;
			}
		}
		line = line->next;
	}
}

void	load_sector(t_engine *engine, t_parsefile *file, t_vtx *vert)
{
	t_parseline	*line;
	t_token		*iter;
	unsigned	pos;

	line = file->first;
	while (line)
	{
		if (line->first)
		{
			if (line->first->type == (1U))
			{
				retrieve_sector(&engine->sectors[pos], line, vert);
				pos++;
			}
		}
		line = line->next;
	}
}

int		load(t_env *env, t_parsefile *file, unsigned nvertex, unsigned nsector)
{
	t_engine	*engine;
	t_vtx		*vert;

	engine = &env->engine;
	engine->nsectors = nsector;
	engine->sectors = malloc(sizeof(t_sector) * nsector);
	vert = (t_vtx *)malloc(sizeof(t_vtx) * nvertex);
	load_vertex(file, vert);
	load_sector(engine, file, vert);
	return(1);
}

int		parser(t_env *env, char *filename)
{
	int			fd;
	t_parsefile	file;
	unsigned	nvertex;
	unsigned	nsector;

	file.first = new_line(0);
	nvertex = 0;
	nsector = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	reader(fd, &file, &nvertex, &nsector);
	// print_file(&file);
	load(env, &file, nvertex, nsector);
	free_file(&file);
	printf("vertexes: %u\n", nvertex);
	printf("sectors: %u\n", nsector);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env 	env;
	if (argc > 1)
	{
		if (argv[1])
			parser(&env, argv[1]);
	}
	return (0);
}