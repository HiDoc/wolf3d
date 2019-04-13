/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/04/12 23:06:31 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	ispoint_inrect(int x, int y, SDL_Rect r)
{
	return (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h);
}

int	new_btn_current(t_bloc *b, int x, int y, int limit)
{
	int	i;

	i = -1;

	while (++i < limit)
	{
		if (ispoint_inrect(x, y, b->rect))
			return (i);
	}
	return (0);
}

// void	action_mainmenu(t_env *e, int x, int y)
// {
// 	int	current;

// 	env->
// }

void	action_menu(t_env *e)
{
	t_menu	*m;
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	m = &e->menu;
	// if (m->status.ingame_menu)

	// if (m->status.home)
	// {

	// }
	// m->status.on = 1;
	// action_mainmenu(e, x, y);
	// if (m->status.on)
	// check_pos
}