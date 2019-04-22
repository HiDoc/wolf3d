/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:15:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/22 11:41:03 by sgalasso         ###   ########.fr       */
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
typedef struct s_l_int			t_l_int;
typedef struct s_l_float		t_l_float;
typedef struct s_projec			t_projec;
typedef struct s_du_int			t_du_int;
typedef struct s_ixy			t_ixy;
typedef struct s_rgba			t_rgba;
typedef struct s_perspective	t_perspective;
typedef struct s_square			t_square;

struct 							s_rgba
{
	Uint8		r;
	Uint8		g;
	Uint8		b;
	Uint8		a;
};

struct 							s_ixy
{
	int			x;
	int			y;
};

struct							s_vtx
{
	float		x;
	float		y;
};

struct							s_vctr
{
	float		x;
	float		y;
	float		z;
};

struct							s_edge
{
	t_vtx		v1;
	t_vtx		v2;
};

struct							s_square
{
	t_edge 		top;
	t_edge 		bot;
};

struct							s_du_int
{
	unsigned	a;
	unsigned	b;
};

struct							s_l_int
{
	int			ceil;
	int			floor;
};

struct							s_l_float
{
	float		ceil;
	float		floor;
};

struct							s_projec
{
	int			y1a;
	int			y1b;
	int			y2a;
	int			y2b;
};

struct							s_perspective
{
	t_vtx		vanish;
	t_vtx		horizon;
	t_vtx		from;
	t_vtx		to;
	t_edge		bot;
	t_edge		top;
	t_l_float	a;
	t_l_float	b;
	size_t		col;
	size_t		row;
	int			height;
	SDL_Surface	*sprite;
};
#endif
