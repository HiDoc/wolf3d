/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/27 13:24:28 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_DEFINE_H
# define WOLF_DEFINE_H
# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include "mlx.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <stdio.h>

# include "libft.h"
# define WIDTH 		env->width
# define HEIGHT 	env->height

# define TEXW 		64
# define TEXH 		64

# define KEY_UP 	126
# define KEY_DOWN 	125
# define KEY_LFT 	123
# define KEY_A      0
# define KEY_X      7
# define KEY_RGT 	124
# define ESC 		53

# define E_MLX		env->mlx.mptr
# define E_WIN		env->mlx.wptr
# define E_IMG		env->mlx.iptr

# define I_IMG		env->mlx.data
# define I_END		env->mlx.endian
# define I_SZL		env->mlx.size_l
# define I_BPP		env->mlx.bpp

#endif
