/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/10 13:19:45 by abaille          ###   ########.fr       */
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
# define W				1000
# define H				800

/*
** FPS frames
*/
# define SCREEN_FPS     60
# define SCREEN_TIC     16

/*
** Define maximum queue in renderer
*/
# define MAXQUEUE		32

/*
** Define visions constants
*/
# define EYEHEIGHT		6
# define DUCKHEIGHT		2.5
# define HEADMARGIN		1
# define KNEEHEIGHT		2
# define NEARZ			1e-4f
# define NEARSIDE		1e-5f
# define FARZ			5
# define FARSIDE		20.f

/*
** Field of view
*/
# define HFOV (.73f * H)
# define VFOV (.2f * H)

/*
** World related constants
*/
# define WORLD_NB_WEAPONS 15
# define WORLD_NB_OBJECTS 15
# define WORLD_NB_SURFACE 15

#endif
