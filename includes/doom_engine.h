/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/23 14:16:53 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_ENGINE_H
# define WOLF_ENGINE_H

/* Define window size */
# define W 800
# define H 600

/* Define various vision related constants */
# define EyeHeight  6    // Camera height from floor when standing
# define DuckHeight 2.5  // And when crouching
# define HeadMargin 1    // How much room above camera before head hits the ceiling

// How tall obstacles the player can simply walk over without jumping
# define KneeHeight 2

# define hfov (0.73f*H)  // Affects the horizontal field of vision
# define vfov (.2f*H)    // Affects the vertical field of vision

// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
# define min(a,b)(((a) < (b)) ? (a) : (b))	// min: Choose smaller of two scalars.
# define max(a,b)(((a) > (b)) ? (a) : (b))	// max: Choose greater of two scalars.
# define clamp(a, mi,ma)min(max(a,mi),ma)	// clamp: Clamp value into set range.
# define vxs(x0,y0, x1,y1)((x0)*(y1) - (x1)*(y0))	// vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
# define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
# define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
# define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_xy) { \
vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

typedef struct	s_xy		t_xy;
typedef struct	s_xyz		t_xyz;
typedef struct	s_sector	t_sector;
typedef struct	s_player	t_player;

struct						s_xy
{
	float			x;
	float			y;
};

struct						s_xyz
{
	float			x;
	float			y;
	float			z;
};

struct						s_sector
{
	float			floor;
	float			ceil;
	t_xy			*vertex;	// Each vertex has an x and y coordinate
	signed char		*neighbors;	// Each edge may have a correspond. neighbor. sector
	unsigned		npoints;	// Number of vertex
};

struct						s_player
{
	t_xyz		where;      // Current position
	t_xyz		velocity;   // Current motion vector
	float		angle;
	float		anglesin;
	float		anglecos;
	float		yaw;		// Looking towards (and sin() and cos() thereof)
	unsigned sector;
};
#endif
