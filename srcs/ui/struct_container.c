/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:07:40 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/03 17:21:27 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_container(t_env *env)
{
	SDL_Surface	*new;

	new = new_surface("walls/01");
	env->world.surfaces.walls[0].sprite = new;
	return (1);
}