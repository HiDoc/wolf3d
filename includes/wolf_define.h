/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/04 18:39:40 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_DEFINE_H

# ifdef __APPLE__
#  include "gl.h"
#  include "glu.h"
#  include "gltypes.h"
# endif

# define WOLF_DEFINE_H
# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include "mlx.h"
//# include "mlx_int.h"
# include "libft.h"
# include "X.h"
//# include "Xlib.h"
# define WIDTH 		800
# define HEIGHT 	600

# define TEXW 		64
# define TEXH 		64

# define KEY_UP 	126
# define KEY_DOWN 	125
# define KEY_LFT 	123
# define KEY_RGT 	124
# define ESC 		53

# define T_T1		env->thw.t1
# define T_T2		env->thw.t2
# define T_T3		env->thw.t3
# define T_T4		env->thw.t4
# define T_T5		env->thw.t5
# define T_T6		env->thw.t6
# define T_T7		env->thw.t7
# define T_T8		env->thw.t8

# define T_TH1		env->thw.t1.th
# define T_TH2		env->thw.t2.th
# define T_TH3		env->thw.t3.th
# define T_TH4		env->thw.t4.th
# define T_TH5		env->thw.t5.th
# define T_TH6		env->thw.t6.th
# define T_TH7		env->thw.t7.th
# define T_TH8		env->thw.t8.th

# define E_MLX		env->mlx.mptr
# define E_WIN		env->mlx.wptr
# define E_IMG		env->mlx.iptr

# define I_IMG		env->mlx.data
# define I_END		env->mlx.endian
# define I_SZL		env->mlx.size_l
# define I_BPP		env->mlx.bpp

#endif
