/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_engine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/20 14:09:27 by fmadura          ###   ########.fr       */
=======
/*   Updated: 2019/03/18 19:32:51 by sgalasso         ###   ########.fr       */
>>>>>>> 4aec3cab2c860d225a105ed1cba070b3a699f4d1
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_ENGINE_H
# define DOOM_S_ENGINE_H

typedef struct	s_scaler	t_scaler;
typedef struct	s_sector	t_sector;
typedef struct	s_player	t_player;
typedef struct	s_item		t_item;
typedef struct	s_engine	t_engine;
typedef struct	s_vision	t_vision;
typedef struct	s_queue		t_queue;
typedef struct	s_raycast	t_raycast;
typedef struct	s_chain		t_chain;


struct						s_scaler
{
	int		result;
	int		bop;
	int		fd;
	int		ca;
	int		cache;
};

struct						s_chain
{
	unsigned	a;
	unsigned	b;
	unsigned	c;
	unsigned	d;
	unsigned	e;
	unsigned	f;
	unsigned	g;
	unsigned	h;
};

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
	t_wrap_sect	*head_object;
	int			nb_objects;
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

struct						s_player
{
	t_vctr		where;
	t_vctr		velocity;
	t_vision	vision;
	float		angle;
	float		anglesin;
	float		anglecos;
	float		yaw;
	unsigned 	sector;
};

struct						s_queue
{
	t_item		queue[MAXQUEUE];
	t_item		*head;
	t_item		*tail;
	t_item		now;
	t_sector	*sect;
	int			ytop[W];
	int			ybottom[W];
	int			*renderedsectors;
};

struct						s_raycast
{
	t_edge			trsl;
	t_edge			rot;
	t_edge			scale;
	t_l_float		lf_current;
	t_l_float		lf_next;
	t_l_int			li_sector;
	t_l_int			li_texture;
	t_projec		p;
	t_projec		n;
	int				x;
	int				x1;
	int				x2;
	int				txtx;
	int				neighbor;
};

struct						s_engine
{
	t_sector		*sectors;
	unsigned		nsectors;
	t_player		player;
};
#endif
