/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/25 19:41:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_DEFINE_H
# define WOLF_DEFINE_H
# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>

# include "libft.h"
# define WIDTH          800
# define HEIGHT 	    600
# define PI             3.141592

# define NEARZ          1e-4f
# define NEARSIDE       1e-5f
# define FARZ           5
# define FARSIDE        20.f

#define WORLD_NB_WEAPONS 15
#define WORLD_NB_OBJECTS 15
#define WORLD_NB_SURFACE 15

#endif
