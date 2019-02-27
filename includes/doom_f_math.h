/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:15:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/27 20:27:00 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_MATH_H
# define DOOM_F_MATH_H

float		cross_product(t_vtx v1, t_vtx v2);
t_vtx		intersect_vtx(t_vtx v1, t_vtx v2, t_vtx v3, t_vtx v4);
t_projec	calc_projection(float p, t_limit_float l, t_edge t, t_edge s);
t_vtx		add_vertex(t_vtx v1, t_vtx v2);
t_vtx		diff_vertex(t_vtx v1, t_vtx v2);
float		pointside(t_vtx p, t_vtx v0, t_vtx v1);
float		clamp(float a, float min, float max);
int			intersect_rect(t_vtx a_up, t_vtx a_bot, t_vtx b_up, t_vtx b_bot);
#endif
