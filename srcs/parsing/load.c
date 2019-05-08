/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:59:53 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/06 19:21:27 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			load_map(t_engine *e, t_env *env)
{
	parser(env, "rsrc/maps/map.txt");
	verify_map(e);
	if ((e->queue.renderedsectors = (int *)malloc(e->nsectors * sizeof(int))) == NULL)
		return;
	return ;
}
