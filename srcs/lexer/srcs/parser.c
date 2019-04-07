/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/07 19:02:32 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int		load(t_env *env, t_parsefile *file, unsigned nvertex, unsigned nsector)
{
	t_engine *engine;

	engine = &env->engine;
	engine->nsectors = nsector;
	engine->sectors = malloc(sizeof(t_sector) * nsector);
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
	print_file(&file);
	free_file(&file);
	printf("\n");
	printf("vertexes: %u\n", nvertex);
	printf("sectors: %u\n", nsector);
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (argv[1])
			parser(argv[1]);
	}
	return (0);
}