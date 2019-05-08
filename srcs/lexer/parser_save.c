/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:33:08 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 15:55:55 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		verify_token_first(int iter, char c, unsigned which)
{
	const t_op	op_first[TOKEN_FRST_MAX] = {
		{(1U << SECTOR), "Sector", &is_sec, 10},
		{(1U << VERTEX), "Vertex", &is_vtx, 2},
		{(1U << PLAYER), "Player", &is_plr, 4},
		{(1U << OBJECT), "Object", &is_obj, 2},
		{(1U << CURRWPN), "CurrentWpn", &is_cur, 1},
		{(1U << ENTITY), "Entity", &is_ent, 4},
		{(1U << WPN), "Weapons", &is_wpn, 4},
		{(1U << GEMS), "Gems", &is_gem, 2},
		{(1U << STATS), "Stats", &is_sts, 13},
		{(1U << SETTG), "Settings", &is_stg, 14},
		{(1U << END), "End", &is_end, 1},
		{(1U << NONE), "None", &no_op_int, 0},
		{(1U << ERROR), "Error", &no_op_int, 0}};

	if (which == TOKEN_VERIF)
		return (op_first[iter].verify(c));
	else
		return (op_first[iter].val);
}

t_token	*new_save_token(char c, unsigned pos)
{
	unsigned	iter;
	unsigned	maxiter;
	t_token		*new;
	int			(*funct)(int, char, unsigned);

	iter = 0;
	maxiter = pos ? TOKEN_NEXT_MAX - 1: TOKEN_FRST_MAX - 1;
	funct = pos ? &verify_token_next : &verify_token_first;
	new = NULL;
	while (iter < maxiter)
	{
		if (funct(iter, c, TOKEN_VERIF))
			break ;
		iter++;
	}
	new = ft_memalloc(sizeof(t_token));
	new->next = NULL;
	new->type = funct(iter, c, TOKEN_VALUE);
	new->pos = pos;
	new->value = c;
	return (new);
}

int		save_reader(int fd, t_parsefile *file, unsigned *nvtx, unsigned *nsct)
{
	char		buffer[2];
	t_parseline	*line;
	t_token		*iter;
	unsigned	nline;
	unsigned	pos;

	line = file->first;
	nline = 0;
	pos = 0;
	while (read(fd, buffer, 1) > 0)
	{
		if (line->first == NULL)
		{
			line->first = new_save_token(*buffer, pos);
			iter = line->first;
			// if (line->first->type == (1U << SECTOR))
			// 	line->absolute = *nsct;
			// if (line->first->type == (1U << VERTEX))
			// 	line->absolute = *nvtx;
			// if (iter->value == 'v')
			// 	(*nvtx)++;
			// if (iter->value == 's')
			// 	(*nsct)++;
			pos++;
		}
		else
		{
			iter->next = new_save_token(*buffer, pos);
			iter = iter->next;
			pos++;
		}
		if (iter->value == '\n')
			set_new_line(&line, &nline, &pos);
	}
	return (1);
}

void	retrieve_save(t_env *e, char *filename)
{
	int			fd;
	t_parsefile	file;

	file.first = new_line(0, 0);
	nvertex = 0;
	nsector = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		doom_error_exit("Doom_Nukem error open file save\n");
	save_reader(fd, &file, &nvertex, &nsector);
	// print_file(&file);
	load(env, &file, nvertex, nsector);
	free_file(&file);
	return (1);
}