/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 13:57:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/21 13:36:29 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_UI
# define DOOM_S_UI

typedef struct s_font		t_font;
typedef struct s_circle		t_circle;
typedef struct s_minimap	t_minimap;

struct 						s_font
{
	SDL_Color			color;
	const char			*str;
	TTF_Font			*font;
	t_vtx				pos;
	int					size;
	int					l;
	int					r;
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
	int					xmin;
	int					xmax;
	int					ymin;
	int					ymax;

	SDL_Surface			*surface;		// calque sectors
	SDL_Surface			*background;	// calque background

	t_vtx				origin; 		// origin minimap on sdl.surface
};

#endif
