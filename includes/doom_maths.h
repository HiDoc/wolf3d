/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_maths.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:15:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/25 21:47:24 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_MATHS_H
# define DOOM_MATHS_H

typedef struct s_vtx			t_vtx;
typedef struct s_vctr			t_vctr;
typedef struct s_edge			t_edge;
typedef struct s_limit_int		t_limit_int;
typedef struct s_limit_float	t_limit_float;
typedef struct s_projec			t_projec;

struct							s_vtx
{
	float	x;
	float	y;
};

struct							s_vctr
{
	float	x;
	float	y;
	float	z;
};

struct							s_edge
{
	t_vtx	v1;
	t_vtx	v2;
};

struct							s_limit_int
{
	int		ceil;
	int		floor;
};

struct							s_limit_float
{
	float	ceil;
	float	floor;
};

struct						s_projec
{
	int		y1a;
	int		y1b;
	int		y2a;
	int		y2b;
};

float							cross_product(t_vtx v1, t_vtx v2);
t_vtx							intersect_vtx(t_vtx v1, t_vtx v2,
								t_vtx v3, t_vtx v4);
t_projec						calc_projection(float p,
								t_limit_float l, t_edge t, t_edge s);
t_vtx   add_vertex(t_vtx v1, t_vtx v2);
t_vtx   diff_vertex(t_vtx v1, t_vtx v2);
float	pointside(t_vtx p, t_vtx v0, t_vtx v1);
int		intersect_rect(t_vtx a_up, t_vtx a_bot, t_vtx b_up, t_vtx b_bot);
#endif
