/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/19 22:57:18 by abaille          ###   ########.fr       */
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

# define W_TEXTURE		256
# define W				800
# define H				600

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
** Movement
*/
# define SPEED_WALK 0.2f
# define SPEED_RUN	0.4f

/*
** Field of view
*/
# define HFOV (.73f * H)
# define VFOV (.2f * H)

/*
** World related constants
*/
# define WORLD_NB_WEAPONS 3
# define WORLD_NB_OBJECTS 6
# define WORLD_NB_SURFACE 15

/*
** Ui put string
*/

#define F_DOOM "rsrc/font/AmazDooMLeft2.ttf"
#define F_TEXT "rsrc/font/interbureau.ttf"
#define F_NUMB "rsrc/font/5E.ttf"

/*
** Colors
*/
#define RED			(SDL_Color){255, 0, 0, 255}
#define WHITE		(SDL_Color){255, 255, 255, 255}
#define BLACK		(SDL_Color){0, 0, 0, 255}
#define BLUE		(SDL_Color){8, 8, 255, 0}
#define	GOLD		(SDL_Color){242, 204, 42, 255}
#define TRANSPARENT	(SDL_Color){0, 0, 0, 0}

#endif
