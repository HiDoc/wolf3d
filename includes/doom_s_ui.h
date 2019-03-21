/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 13:57:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/21 18:07:30 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_UI
# define DOOM_S_UI

typedef struct s_uinv		t_uinv;
typedef struct s_hud		t_hud;
typedef struct s_font		t_font;
typedef struct s_circle		t_circle;
typedef struct s_minimap	t_minimap;

struct 						s_font
{
	SDL_Color			color;
	const char			*str;
	const char			*font;
	t_vtx				pos;
	int					size;
	int					l;
	int					r;
};


struct						s_hud
{
	SDL_Surface			*bar[2];
	SDL_Surface			*faces[4];
	SDL_Surface			*hud_wpn[3];
	SDL_Surface			*empty_b;
	SDL_Surface			*objects[6];
	t_wrap_inv			*shortcut[6];
	int					is_txt;
	int					mix;
};

struct 						s_uinv
{
	SDL_Surface			*front_pic;
	SDL_Surface			*mini_wpn[3];
	SDL_Surface			*empt_wpn[3];
	SDL_Surface			*icon[2];
	SDL_Surface			*box[2];
	t_edge				blocs[6];
	t_edge				wblocs[3];
	t_edge				iblocs[3];
	int					is_active;
	int					wwheel;
	int					nb_wpn;
};

struct						s_circle
{
	float				x;
	float				y;
	float				radius;
	Uint32				color;
};

struct						s_minimap
{
	t_vtx				origin; 	// origin minimap
	t_vtx				player; 	// player pos relatif minimap
	SDL_Surface			*surface;	// calque precalcule
	SDL_Surface			*rot_srf;	// intermediaire rotation
};

#endif
