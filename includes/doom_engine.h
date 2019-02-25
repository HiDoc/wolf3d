/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/25 13:58:35 by fmadura          ###   ########.fr       */
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
typedef struct	s_item		t_item;
typedef struct	s_engine	t_engine;
typedef struct	s_projec	t_projec;
typedef struct	s_ylevel	t_ylevel;
typedef struct	s_vision	t_vision;
typedef struct	s_vertex	t_vertex;

struct						s_vertex
{
	float		x1;
	float		y1;
	float		x2;
	float		y2;
};

struct						s_ylevel
{
	float		yceil;
	float		yfloor;
	float		nyceil;
	float		nyfloor;
};

struct						s_projec
{
	int			y1a;
	int			y1b;
	int			y2a;
	int			y2b;
};

struct						s_item
{
	int			sectorno;
	int			sx1;
	int			sx2;
};

struct						s_xy
{
	float		x;
	float		y;
};

struct						s_xyz
{
	float		x;
	float		y;
	float		z;
};

struct						s_sector
{
	float		floor;
	float		ceil;
	t_xy		*vertex;	// Each vertex has an x and y coordinate
	signed char	*neighbors;	// Each edge may have a correspond. neighbor. sector
	unsigned	npoints;	// Number of vertex
};

struct						s_player
{
	t_xyz		where;      // Current position
	t_xyz		velocity;   // Current motion vector
	float		angle;
	float		anglesin;
	float		anglecos;
	float		yaw;		// Looking towards (and sin() and cos() thereof)
	unsigned 	sector;
};

struct						s_vision
{
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
	float           yaw;
	float           eyeheight;
};

struct						s_engine
{
	SDL_Surface	*surface;
	t_sector	*sectors;
	unsigned	NumSectors;
	t_player	player;
};

void	LoadData(t_engine *e);
void	UnloadData(SDL_Texture *texture, SDL_Renderer *renderer,
		SDL_Window *window, t_engine *e);
void	DrawScreen(t_engine *e);
int		is_bumping(const t_sector *sect, float eyeheight,
		unsigned s, t_engine *e);
int		is_crossing(const t_xy p, t_xy d, const t_xy *vert,
		unsigned s, t_engine *e);
void	bumping_score(t_xy *d, t_xy b);

void	player_moving(t_vision *v, int set, t_engine *e);
void	player_falling(t_vision *v, t_engine *e);
void	player_collision(t_engine *e, t_vision *v);

int		sdl_render(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e);
int		sdl_loop(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e);
#endif
