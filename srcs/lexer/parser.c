/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 16:27:33 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void	select_type_sector(t_sector *sect)
{
	if (sect->type == 0x00)
		sect->is_door = 0x00;
}

void 	retrieve_sector(t_sector *sect, t_parseline *line, t_vtx *vtx)
{
	t_token		*iter;
	unsigned	number;
	unsigned	count;
	unsigned	pos;

	number = token_calc(line) - 3;
	//printf("number of vertexes: %u\n", number);
	sect->npoints = number;
	sect->neighbors = ft_memalloc(sizeof(signed) * number);
	sect->vertex = ft_memalloc(sizeof(t_vtx) * (sect->npoints + 1));
	ft_memset(sect->neighbors, -1, number);
	iter = line->first;
	if (iter)
		iter = iter->next;
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
			if (iter->next && iter->next->type != (1U << 2))
			{
				if (count == 2)
					sect->type = pos;
				if (count > 2)
				{
					sect->vertex[count - 2] = (t_vtx){vtx[pos].x, vtx[pos].y};
					//printf("Vertex: [%.0f, %.0f] pos: %u\n", vtx[pos].x, vtx[pos].y, pos);
				}
				count++;
				pos = 0;
			}
		}
		iter = iter->next;
	}
	select_type_sector(sect);
	if (count > 2)
		sect->vertex[0] = (t_vtx){sect->vertex[sect->npoints].x,
		sect->vertex[sect->npoints].y};
	//printf("Vertex: [%.0f, %.0f]\n", vtx[0].x, vtx[0].y);
}

void 	retrieve_player(t_engine *engine, t_parseline *line)
{
	t_token		*iter;
	float		*value;
	float		x;
	float		y;
	float		n;

	iter = line->first;
	x = 0;
	y = 0;
	n = 0;
	if (iter)
		iter = iter->next;
	value = &x;
	while (iter)
	{
		if (iter->type == (1U << 2))
			*value = *value * 10 + (iter->value - '0');
		if (iter->type == (1U << 2) && (iter->next && iter->next->type != (1U << 2)))
		{
			if (value == &x)
				value = &y;
			else if (value == &y)
				value = &engine->player.angle;
			else if (value == &engine->player.angle)
				value = &n;
		}
		iter = iter->next;
	}
	engine->player.where = (t_vctr) {x, y, EYEHEIGHT};
	engine->player.sector = n;
	//printf("player :%.0f, %.0f, %.0f, %.0f\n", x, y, engine->player.angle, n);
}

void	load_vertex(t_parsefile *file, t_vtx *vert)
{
	t_parseline	*line;
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
				//printf("v %.0f %.0f \n", vert[pos].x, vert[pos].y);
				pos++;
			}
		}
		line = line->next;
	}
}

void	load_sector(t_engine *engine, t_parsefile *file, t_vtx *vert)
{
	t_parseline	*line;
	unsigned	pos;

	line = file->first;
	pos = 0;
	while (line)
	{
		if (line->first)
		{
			if (line->first->type == (1U))
			{
				//printf("Currently on sector : %u\n", pos);
				retrieve_sector(&engine->sectors[pos], line, vert);
				pos++;
			}
			if (line->first->type == (1U << 2))
				retrieve_player(engine, line);
		}
		line = line->next;
	}
}

void	retrieve_object(t_engine *engine, t_parseline *line)
{
	t_token		*iter;
	t_vtx		pos;
	t_vtx		ref;
	float		s;
	float		*ptr;

	iter = line->first;
	if (iter)
		iter = iter->next;
	ptr = &pos.x;
	s = 0;
	pos = (t_vtx) {0, 0};
	ref = (t_vtx) {0, 0};
	while (iter)
	{
		if (iter->type == (1U << 2))
		{
			*ptr = (*ptr * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != (1U << 2))
			{
				if (ptr == &pos.x)
					ptr = &pos.y;
				else if (ptr == &pos.y)
					ptr = &s;
				else if (ptr == &s)
					ptr = &ref.x;
				else if (ptr == &ref.x)
					ptr = &ref.y;
			}
		}
		iter = iter->next;
	}
	//printf("object %.0f %.0f %.0f %.0f %.0f\n", pos.x, pos.y, s, ref.x, ref.y);
	fill_objects_sector(&engine->sectors[(unsigned)s], pos, ref.x, ref.y);
}

void	retrieve_enemy(t_engine *engine, t_parseline *line)
{
	t_token		*iter;
	t_vtx		pos;
	t_vtx		ref;
	float		s;
	float		*ptr;

	iter = line->first;
	pos = (t_vtx) {0, 0};
	ref = (t_vtx) {0, 0};
	if (iter)
		iter = iter->next;
	ptr = &pos.x;
	while (iter)
	{
		if (iter->type == (1U << 2))
		{
			*ptr = (*ptr * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != (1U << 2))
			{
				if (ptr == &pos.x)
					ptr = &pos.y;
				else if (ptr == &pos.y)
					ptr = &s;
				else if (ptr == &s)
					ptr = &ref.x;
				else if (ptr == &ref.x)
					ptr = &ref.y;
			}
		}
		iter = iter->next;
	}
	//printf("enemy %.0f %.0f %.0f %.0f\n", pos.x, pos.y, s, ref.x);
	fill_objects_sector(&engine->sectors[(unsigned)s], pos, ref.x, ref.y);
}

void	load_object(t_engine *engine, t_parsefile *file)
{
	t_parseline	*line;

	line = file->first;
	while (line)
	{
		if (line->first)
		{
			if (line->first->type == (1U << 3))
				retrieve_object(engine, line);
			if (line->first->type == (1U << 6))
				retrieve_enemy(engine, line);
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
	engine->sectors = ft_memalloc(sizeof(t_sector) * nsector);
	vert = (t_vtx *)ft_memalloc(sizeof(t_vtx) * nvertex);
	load_vertex(file, vert);
	load_sector(engine, file, vert);
	load_object(engine, file);
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
	print_file(&file);
	load(env, &file, nvertex, nsector);
	free_file(&file);
	env->engine.nsectors = nsector;
	//printf("vertexes: %u\n", nvertex);
	//printf("sectors: %u\n", nsector);
	return (1);
}
