
#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include "mlx.h"
# include "libft.h"
# include "X.h"
# include <pthread.h>

# define WIDTH 800
# define HEIGHT 600
# define TEXW 64
# define TEXH 64
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LFT 123
# define KEY_RGT 124
# define ESC 53

typedef struct  s_mlx
{
	void	*mptr;
	void	*wptr;
	void	*iptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}               t_mlx;

typedef	struct	s_xy
{
	double	x;
	double	y;
}				t_xy;

typedef struct  s_env
{
	t_mlx   *mlx;
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
}               t_env;

int		wolf(t_env *env);

void    print_error(int nb, t_env *env);
void    free_env(t_env *env);

int		key_hook(int key, t_env *env);
#endif
