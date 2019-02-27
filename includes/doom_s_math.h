/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:15:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/27 20:31:48 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_MATHS_H
# define DOOM_S_MATHS_H

/*
** 1 : Vertex
** 2 : Vectors
** 3 : Edge
** 4 : Limit of floor and ceil in integer
** 5 : Limit of floor and ceil in float
** 6 : Perspective projection of an edge
*/
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

struct							s_projec
{
	int		y1a;
	int		y1b;
	int		y2a;
	int		y2b;
};

#endif
