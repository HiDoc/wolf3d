/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2018/08/29 11:58:22 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_STRUCT_H
# define WOLF_STRUCT_H

typedef struct s_mlx	t_mlx;
typedef struct s_env	t_env;
typedef struct s_xy		t_xy;

struct					s_mlx
{
	void	*mptr;
	void	*wptr;
	void	*iptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
};

struct					s_xy
{
	double	x;
	double	y;
};

struct					s_env
{
	t_mlx	*mlx;
	t_xy	pos;
	t_xy	dir;
	t_xy	plane;
	t_xy	sidedist;
	t_xy	delta;
	t_xy	raydir;
	double	cam;
	double	wdist;
	double	ang;
	int		**w_map;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineh;
	int		sdraw;
	int		edraw;
};

#endif
