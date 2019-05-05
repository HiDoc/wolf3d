/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:08:36 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 17:18:09 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


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

void		load_player(t_env *e, t_parseline *line, t_vtx *vert)
{
	(void)vert;
	retrieve_player(e, line);
}