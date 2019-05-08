/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 22:39:22 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 22:39:36 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void				render_nfloor(t_drawline l, t_env *env)
{
	vline(l, env);
}

void				render_nceil(t_drawline l, t_env *env)
{
	vline(l, env);
}

void				render_nwall(t_drawline l, t_env *env)
{
	render_cwall(l, env);
}
