/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/04 14:42:01 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_STRUCT_H
# define WOLF_STRUCT_H

typedef struct s_env	t_env;
typedef struct s_point	t_point;
typedef struct s_thr	t_thr;
typedef struct s_thw	t_thw;
typedef struct s_line	t_line;
typedef struct s_ray	t_ray;
typedef struct s_portal	t_portal;
typedef struct s_sdl	t_sdl;
typedef struct s_hub	t_hub;
typedef struct s_msc	t_msc;
typedef struct s_wobj	t_wobj;

struct					s_sdl
{
	Uint32			pixels[800 * 600];
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Surface		*surface;	
	SDL_Event		event;
};

struct					s_point
{
	double		x;
	double		y;
};

struct					s_thr
{
	pthread_t	th;
	t_env		*env;
	int			nbr;
};

struct					s_line
{
	SDL_Surface	*text;
	SDL_Surface	*floor;
	SDL_Surface	*sky;
	t_point		map;
	t_point		delta;
	t_point		step;
	t_point		raydir;	
	t_point		wall;
	t_point		side;
	double		wdist;
	int			sidew;
	int			lineh;
	int			sdraw;
	int			edraw;
};

struct					s_hub
{
	SDL_Texture		*texture;
	SDL_Surface		*surface;
	SDL_Rect		rect;
	SDL_Color		color;
	TTF_Font		*font;
	SDL_Surface		*img;
	int				size;
	double			ang;
	int				w;
	int				h;
	t_point			pt;
};

struct					s_portal
{
	SDL_Surface	*inimg;
	SDL_Surface	*outimg;
	t_point		inplane;
	t_point		indir;
	t_point		inpos;
	t_point		outplane;
	t_point		outdir;
	t_point		outpos;
	t_point		inemp;
	t_point		outemp;
	int			in;
	int			out;
	int			hit;
};

struct					s_msc
{
	Mix_Music	*load;
	Mix_Chunk	*shot;
};

struct					s_wobj
{
	int			hit;
	t_point		pos;
	SDL_Surface	*simpact;
	int			poster;
	int			impact;
	int			index;
	SDL_Surface	*posters[8];
	SDL_Surface	*wposters[8];
	int			is_bullet;
};

struct					s_env
{
	t_sdl		sdl;
	t_thr		thr[8];
	t_point		pos;
	t_point		dir;
	t_point		plane;
	double		is_updn;
	double		cam;
	double		ang;
	double		pang;
	int			**w_map;
	int			**o_map;
	SDL_Surface	*wall;
	SDL_Surface	*walls[10];
	SDL_Surface	*enemy;
	SDL_Surface	*floor;
	SDL_Surface	*sky;
	SDL_Surface	*gun;
	SDL_Surface	*gun_impact;
	SDL_Surface	*ak_frms[43];
	SDL_Surface	*mitra_frms[36];
	SDL_Surface	*stitch[18];
	SDL_Surface	*bul_surf[6];
	int			ld_wp;
	int			width;
	int			height;
	t_portal	portal;
	t_hub		lscreen;
	t_hub		title;
	t_hub		life;
	t_hub		logo;
	double		hratio;
	int			is_jump;
	t_msc		sounds;
	t_wobj		wobj;
	t_point		mouse;
};

#endif
