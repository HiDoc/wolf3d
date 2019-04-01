/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/29 20:36:24 by fmadura          ###   ########.fr       */
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

# define W_TEXT			256
# define W				1200
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
# define EYEHEIGHT		8
# define DUCKHEIGHT		3
# define HEADMARGIN		1
# define KNEEHEIGHT		3
# define NEARZ			1e-4f
# define NEARSIDE		1e-5f
# define FARZ			5
# define FARSIDE		20.f

/*
** Movement
*/
# define SPEED_WALK 0.4f
# define SPEED_RUN	0.8f

/*
** Field of view
*/
# define HFOV (.73f * H)
# define VFOV (.2f * H)

/*
** World related constants
*/
# define WORLD_NB_WEAPONS	3
# define WORLD_NB_OBJECTS	13
# define WORLD_NB_GEMS		4
# define WORLD_NB_CSMBLE	6
# define WORLD_NB_SURFACE	15
# define WORLD_NB_POSTERS	10
# define WORLD_NB_WALLS		5
# define WORLD_NB_FLOORS	4
# define WORLD_NB_ENEMIES	1

/*
** Colors
*/
#define RED			(SDL_Color){255, 0, 0, 255}
#define WHITE		(SDL_Color){255, 255, 255, 255}
#define BLACK		(SDL_Color){0, 0, 0, 255}
#define BLUE		(SDL_Color){8, 8, 255, 0}
#define	GOLD		(SDL_Color){242, 204, 42, 255}
#define TRANSPARENT	(SDL_Color){0, 0, 0, 0}

/*
** Sounds
*/
# define SHOT_MAGNUM "rsrc/sound/shot/magnum.wav"
# define SHOT_SHOTGUN "rsrc/sound/shot/shotgun.wav"
# define SHOT_RIFLE "rsrc/sound/shot/rifle.wav"

#endif
