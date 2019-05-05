/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 19:38:55 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

typedef struct s_op_ft
{
	unsigned	val;
	void		(*retrieve)(t_env *, t_parseline *, t_vtx *);
} t_op_ft;

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
		if (op_first[iter].val == type)
			return op_first[iter].retrieve;
		iter++;
	}
	return (NULL);
}

// void	load_iter(t_token *iter)
// {
// 	unsigned	value;
// 	unsigned	count;

// 	value = 0;
// 	count = 0;
// 	while (iter)
// 	{
// 		if (iter->type == (1U << POINT))
// 			break;
// 		if (iter->type == (1U << INT))
// 		{
// 			value = (value * 10) + (iter->value - '0');
// 			if (iter->next && iter->next->type != (1U << INT))
// 			{
// 				fill_sector(sect, value, count);
// 				value = 0;
// 				count++;
// 			}
// 		}
// 		iter = iter->next;
// 	}
// }

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
	unsigned	nvertex;
	unsigned	nsector;

	file.first = new_line(0, 0);
	nvertex = 0;
	nsector = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	reader(fd, &file, &nvertex, &nsector);
	print_file(&file);
	load(env, &file, nvertex, nsector);
	free_file(&file);
	env->engine.nsectors = nsector;
	return (1);
}
