/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/27 20:15:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_DEFINE_H
# define DOOM_DEFINE_H
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
# define PI             3.141592

/* 
** Define window size
*/
# define W				800
# define H				600

/*
** Define maximum queue in renderer
*/
# define MaxQueue		32

/*
** Define visions constants
*/
# define EyeHeight		6    
# define DuckHeight		2.5
# define HeadMargin		1
# define KneeHeight		2
# define NEARZ			1e-4f
# define NEARSIDE		1e-5f
# define FARZ			5
# define FARSIDE		20.f

/*
** Field of view
*/
# define hfov (0.73f * H)
# define vfov (.2f * H)

/*
** World related constants
*/
#define WORLD_NB_WEAPONS 15
#define WORLD_NB_OBJECTS 15
#define WORLD_NB_SURFACE 15

#endif
