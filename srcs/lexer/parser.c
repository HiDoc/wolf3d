/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:07 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 15:44:45 by fmadura          ###   ########.fr       */
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

unsigned	token_count_until(t_token *start, unsigned type, unsigned until)
{
	unsigned	count;
	t_token		*iter;

	count = 0;
	iter = start;
	while (iter)
	{
		if (iter->type == (1U << until))
			break;
		if (iter->type == (1U << type) &&
			(iter->next && iter->next->type != (1U << type)))
			count++;
		iter = iter->next;
	}
	return (count);
}

unsigned	token_count(t_parseline *line, unsigned type)
{
	t_token		*iter;
	unsigned	count;

	iter = line->first;
	count = 0;
	while (iter)
	{
		if (iter->type == (1U << type) &&
			(iter->next && iter->next->type != (1U << type)))
			count++;
		iter = iter->next;
	}
	return (count);
}

void	fill_sector(t_sector *sect, unsigned value, unsigned count)
{
	if (count == 0)
		sect->ceil = value;
	else if (count == 1)
		return ;
	else if (count == 2)
		sect->floor = value;
	else if (count == 3)
		return ;
	else if (count == 4)
		sect->gravity = value;
	else if (count == 5)
		sect->has_skybox = value;
	else if (count == 6)
		sect->type = value;
}

void 	retrieve_sector(t_sector *sect, t_parseline *line, t_vtx *vtx)
{
	t_token		*iter;
	unsigned	value;
	unsigned	count;

	iter = line->first;
	value = 0;
	count = 0;
	if (iter)
		iter = iter->next;
	else
		return;
	while (iter)
	{
		if (iter->type == (1U << POINT))
			break;
		if (iter->type == (1U << INT))
		{
			value = (value * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != (1U << INT))
			{
				fill_sector(sect, value, count);
				value = 0;
				count++;
			}
		}
		iter = iter->next;
	}
	printf("%f, 0, %f, 0, %d, %d, %d \n",
		sect->ceil, sect->floor, sect->gravity, sect->has_skybox, sect->type);
	count = 1;
	value = 0;
	if (iter && iter->type == (1U << POINT))
	{
		iter = iter->next;
		sect->npoints = token_count_until(iter, INT, POINT);
		printf("npoints :%d\n", sect->npoints);
		sect->vertex = ft_memalloc(sizeof(t_vtx) * (sect->npoints + 1));
		sect->neighbors = ft_memalloc(sizeof(signed char) * sect->npoints);
		ft_memset(sect->neighbors, -1, sizeof(signed char) * sect->npoints);
		while (iter)
		{
			if (iter->type == (1U << POINT))
				break;
			if (iter->type == (1U << INT))
			{
				value = (value * 10) + (iter->value - '0');
				if (iter->next && iter->next->type != (1U << INT))
				{
					sect->vertex[count] = (t_vtx){vtx[value].x, vtx[value].y};
					printf("[vtx: %d] [value: %d] [%f, %f]\n", count, value, vtx[value].x, vtx[value].y);
					value = 0;
					count++;
				}
			}
			iter = iter->next;
		}
		sect->vertex[0] = (t_vtx){sect->vertex[sect->npoints].x, sect->vertex[sect->npoints].y};
		printf("[vtx: %d] [value: %d] [%f, %f]\n", 0, 0, sect->vertex[0].x, sect->vertex[0].y);
	}
	count = 0;
	value = 0;
	if (iter && iter->type == (1U << POINT))
	{
		iter = iter->next;
		sect->textures = ft_memalloc(sizeof(signed char) * (sect->npoints + 1));
		while (iter)
		{
			if (iter->type == (1U << POINT))
				break;
			if (iter->type == (1U << INT))
			{
				value = (value * 10) + (iter->value - '0');
				if (iter->next && iter->next->type != (1U << INT))
				{
					sect->textures[count] = value;
					value = 0;
					count++;
				}
			}
			iter = iter->next;
		}
	}
}

void 	retrieve_player(t_env *e, t_parseline *line)
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
				value = &e->engine.player.angle;
			else if (value == &e->engine.player.angle)
				value = &n;
		}
		iter = iter->next;
	}
	e->engine.player.where = (t_vctr) {x, y, EYEHEIGHT};
	e->engine.player.sector = n;
	e->player.health = 200;
	e->player.shield = 200;
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

void	load_sector(t_env *e, t_parsefile *file, t_vtx *vert)
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
				retrieve_sector(&e->engine.sectors[pos], line, vert);
				pos++;
			}
			if (line->first->type == (1U << 2))
				retrieve_player(e, line);
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
	fill_objects_sector(&engine->sectors[(unsigned)s], pos, (t_ixy){ref.x, s}, ref.y);
}

void	retrieve_enemy(t_env *e, t_parseline *line)
{
	t_token		*iter;
	t_vtx		pos;
	t_vtx		ref;
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
					ptr = &ref.x;
				else if (ptr == &ref.x)
					ptr = &ref.y;
			}
		}
		iter = iter->next;
	}
	//printf("enemy %.0f %.0f %.0f %.0f\n", pos.x, pos.y, ref.x);
	fill_enemies_sector(e, &e->engine.sectors[(unsigned)ref.x], pos, ref.y);
}

void	load_object(t_env *e, t_parsefile *file)
{
	t_parseline	*line;
	t_engine	*engine;

	engine = &e->engine;
	line = file->first;
	while (line)
	{
		if (line->first)
		{
			if (line->first->type == (1U << 3))
				retrieve_object(engine, line);
			if (line->first->type == (1U << 6))
				retrieve_enemy(e, line);
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
	load_sector(env, file, vert);
	load_object(env, file);
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
