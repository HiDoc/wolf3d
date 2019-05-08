/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 17:57:31 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	*load_function(unsigned type)
{
	unsigned 		iter;
	const t_op_ft	op_first[TOKEN_FRST_MAX] = {
		{(1U << SECTOR), &load_sector},
		{(1U << VERTEX), &load_vertex},
		{(1U << PLAYER), &load_player},
		{(1U << OBJECT), &load_object},
		{(1U << SKYBOX), &load_skybox},
		{(1U << ENTITY), &load_entity},
		{(1U << COMMNT), &load_comment},
		{(1U << TXTURE), &load_texture},
		{(1U << MUSIC), &load_music},
		{(1U << END), &no_op_ft},
		{(1U << NONE), NULL},
		{(1U << ERROR), NULL}};

	iter = 0;
	while (iter < NONE)
	{
		if (op_first[iter].val == (1U << type))
			return op_first[iter].retrieve;
		iter++;
	}
	return (NULL);
}

void	*pre_load(t_env *env, t_vtx *vert, unsigned nsector, unsigned nvertex)
{
	t_engine	*engine;

	engine = &env->engine;
	engine->nsectors = nsector;
	engine->sectors = ft_memalloc(sizeof(t_sector) * nsector);
	return (vert = (t_vtx *)ft_memalloc(sizeof(t_vtx) * nvertex));
}

int		load(t_env *env, t_parsefile *file, unsigned nvertex, unsigned nsector)
{
	t_vtx		*vert;
	t_parseline	*line;
	int			(*retrieve)(t_env *, t_parseline *, t_vtx *);

	vert = NULL;
	vert = pre_load(env, vert, nsector, nvertex);
	line = file->first;
	while (line)
	{
		if (line->first && (retrieve = load_function(line->first->type)))
			retrieve(env, line, vert);
		line = line->next;
	}
	return (1);
}

int		parser(t_env *env, char *filename)
{
	int			fd;
	t_parsefile	file;

	ft_bzero(&file, sizeof(t_parsefile));
	file.first = new_line(0, 0);
	fd = open(filename, O_RDONLY);
	reader(fd, &file);
	print_file(&file);
	env->engine.nsectors = file.nsector;
	env->engine.nvertex = file.nvertex;
	if (!lexer(&file))
	{
		free_file(&file);
		doom_error_exit("Invalid map");
	}
	load(env, &file, file.nvertex, file.nsector);
	free_file(&file);
	printf("%u\n", file.nsector);
	return (1);
}
