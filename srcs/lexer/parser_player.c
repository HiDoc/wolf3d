/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:08:36 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 16:58:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_player(t_player *player, unsigned value, unsigned count)
{
	if (count == 0)
		player->where.x = value;
	else if (count == 1)
		player->where.y = value;
	else if (count == 2)
		player->angle = value;
	else if (count == 3)
		player->sector = value;
}

void 	retrieve_player(t_env *e, t_parseline *line)
{
	t_token		*iter;
	unsigned	value;
	unsigned	count;

	iter = line->first;
	if (iter)
		iter = iter->next;
	value = 0;
	count = 0;
	while (iter)
	{
		if (iter->type == INT)
		{
			value = value * 10 + (iter->value - '0');
			if (iter->next && iter->next->type != INT)
			{
				fill_player(&e->engine.player, value, count);
				value = 0;
				count++;
			}
		}
		iter = iter->next;
	}
}

void		load_player(t_env *e, t_parseline *line, t_vtx *vert)
{
	(void)vert;
	retrieve_player(e, line);
	e->player.health = 200;
	e->player.shield = 200;
	e->engine.player.anglecos = 1;
	e->engine.player.anglesin = 0;
}