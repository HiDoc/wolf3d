/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/27 16:33:27 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_ENGINE_H
# define WOLF_ENGINE_H

/* Define window size */
# define W 800
# define H 600
# define MaxQueue 32

/* Define various vision related constants */
# define EyeHeight  6    // Camera height from floor when standing
# define DuckHeight 2.5  // And when crouching
# define HeadMargin 1    // How much room above camera before head hits the ceiling

// How tall obstacles the player can simply walk over without jumping
# define KneeHeight 2

# define hfov (0.73f * H)  // Affects the horizontal field of vision
# define vfov (.2f * H)    // Affects the vertical field of vision

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

typedef struct	s_sector	t_sector;
typedef struct	s_player	t_player;
typedef struct	s_item		t_item;
typedef struct	s_engine	t_engine;
typedef struct	s_vision	t_vision;
typedef struct	s_queue		t_queue;
typedef struct	s_transf	t_transf;

struct						s_item
{
	int			sectorno;
	int			sx1;
	int			sx2;
};

struct						s_sector
{
	float		floor;
	float		ceil;
	t_vtx		*vertex;
	signed char	*neighbors;
	unsigned	npoints;
};

struct						s_player
{
	t_vctr		where;      // Current position
	t_vctr		velocity;   // Current motion vector
	float		angle;
	float		anglesin;
	float		anglecos;
	float		yaw;
	unsigned 	sector;
};

struct						s_queue
{
	t_item		queue[MaxQueue];
	t_item		*head;
	t_item		*tail;
	t_item		now;
	t_sector	*sect;
	int			ytop[W];
	int			ybottom[W];
	int			*renderedsectors;
};

struct						s_vision
{
	int			ground;
	int			falling;
	int			moving;
	int			ducking;
	float		yaw;
	float		eyeheight;
};

struct						s_transf
{
	t_edge			v;
	t_edge			t;
	t_edge			scale;
	t_limit_float	lf_current;
	t_limit_float	lf_next;
	t_projec		p;
	t_projec		n;
	int				x;
	int				x1;
	int				x2;
	int				neighbor;
};

struct						s_engine
{
	SDL_Surface	*surface;
	t_sector	*sectors;
	unsigned	NumSectors;
	t_player	player;
};

void		LoadData(t_engine *e);
void		UnloadData(SDL_Texture *texture, SDL_Renderer *renderer,
			SDL_Window *window, t_engine *e);
void		DrawScreen(t_engine *e);
int			is_bumping(const t_sector *sect, float eyeheight,
			unsigned s, t_engine *e);
int			is_crossing(const t_vtx p, t_vtx d, const t_vtx *vert, unsigned s);
void		bumping_score(t_vtx *d, t_vtx b);

void		player_moving(t_vision *v, int set, t_engine *e);
void		player_falling(t_vision *v, t_engine *e);
void		player_collision(t_engine *e, t_vision *v);

int			sdl_render(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e);
int			sdl_loop(SDL_Texture *texture, SDL_Renderer *renderer, t_engine *e);

t_edge		current_edge(t_vctr player_position, t_vtx v1, t_vtx v2);
t_edge 		rotation_edge(t_player player, t_edge v);
t_edge 		scale_edge(t_edge t);
void		clip_view(t_edge *t);

int			ini_queue(t_engine *e, t_queue *q);

void		vline(t_drawline line, t_engine *e);
int			transform_vertex(t_engine *e, t_queue *q, t_transf *ctn, int s);
#endif
