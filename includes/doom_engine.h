/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/23 13:58:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_xy		t_xy;
typedef struct	s_xyz		t_xyz;
typedef struct	s_sector	t_sector;
typedef struct	s_payer		t_player;

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
	t_xyz		where,      // Current position
	t_xyz		velocity;   // Current motion vector
	float		angle;
	float		anglesin;
	float		anglecos;
	float		yaw;		// Looking towards (and sin() and cos() thereof)
	unsigned sector;
};
