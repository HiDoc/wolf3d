/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:15:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/22 11:41:10 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_MATH_H
# define DOOM_F_MATH_H

float		pointside(t_vtx p, t_vtx v0, t_vtx v1);
float		cross_product(t_vtx v1, t_vtx v2);
float		clamp(float a, float min, float max);

t_vtx		intersect_vtx(t_vtx v1, t_vtx v2, t_vtx v3, t_vtx v4);
t_vtx		add_vertex(t_vtx v1, t_vtx v2);
t_vtx		diff_vertex(t_vtx v1, t_vtx v2);
int         equal_vertex(t_vtx v1, t_vtx v2);
float       dist_vertex(t_vtx a, t_vtx b);

int			edge_parallel(t_edge e1, t_edge e2);
int         equal_edge(t_edge e1, t_edge e2);
int         intersec_edge(t_vtx v0, t_vtx v1, t_vtx v2, t_vtx v3);
int			intersect_rect(t_vtx a_up, t_vtx a_bot, t_vtx b_up, t_vtx b_bot);

void		draw_perspective(SDL_Surface *surface,
			t_square square, t_vtx horizon, t_vtx vanish);
t_vtx		bezier_curve(t_edge e, t_vtx c_point, float time);
t_projec	calc_projec(float pyaw, t_l_float lim, t_edge rot, t_edge scale);
#endif
