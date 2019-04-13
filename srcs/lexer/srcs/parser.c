/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/13 19:59:53 by fmadura          ###   ########.fr       */
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

void 	retrieve_sector(t_parseline *line, t_vtx *vtx)
{
	t_token		*iter;
	float		sfloor;
	float		sceil;
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
			if (line->first->type == (1U))
			{
				retrieve_sector(line, vert);
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