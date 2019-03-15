/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:26:20 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/06 21:48:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_STRUCT_H
# define LIBUI_STRUCT_H

typedef struct  s_pos   t_pos;
typedef struct  s_vec   t_vec;
typedef struct  s_rect  t_rect;
typedef struct  s_circ  t_circ;
typedef struct  s_sdl   t_sdl;
typedef struct  s_square    t_square;
typedef struct  s_round     t_round;
typedef struct  s_objs  t_objs;
typedef struct  s_data  t_data;

struct					s_pos
{
	float				x;
	float				y;
};

struct					s_vec
{
	t_pos			a;
	t_pos			b;
};

struct					s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
	Uint32			color;
};

struct					s_circ
{
	int				x;
	int				y;
	int				radius;
	Uint32			color;
};

struct					s_sdl
{
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
};

struct					s_square
{
	int				index;
	int				group;
	t_rect			rect;
};

struct					s_round
{
	int				index;
	int				group;
	t_circ			circ;
};

struct					s_objs
{
	int				circle_index;
	t_round			circle[200];
	int				square_index;
	t_square		square[200];
};

struct					s_data
{
	t_sdl			sdl;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	TTF_Font		*font;

	t_objs			objects;

	const Uint8 *state;
	int			mouse_x;
	int			mouse_y;
	t_pos		mouse;

	int			nb_frames;
};

#endif
