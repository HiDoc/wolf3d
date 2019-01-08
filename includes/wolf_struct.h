/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/08 13:52:32 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_STRUCT_H
# define WOLF_STRUCT_H

typedef struct s_env		t_env;
typedef struct s_sdl		t_sdl;
typedef struct s_minimap	t_minimap;

typedef struct s_point		t_point;
typedef struct s_thr		t_thr;

typedef struct s_line		t_line;
typedef struct s_obj		t_obj;
typedef struct s_iline		t_iline;

typedef struct s_portal		t_portal;
typedef struct s_hub		t_hub;
typedef struct s_msc		t_msc;
typedef struct s_wobj		t_wobj;
typedef struct s_limit		t_limit;

/*
**	Gameplay Structure
*/

typedef struct s_object		t_object;
typedef struct s_world		t_world;
typedef struct s_wall		t_wall;
typedef struct s_weapon		t_weapon;
typedef struct s_action		t_action;
typedef struct s_inventory	t_inventory;
typedef struct s_character	t_character;

struct					s_sdl
{
	Uint32			pixels[WIDTH * HEIGHT];
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

struct					s_obj
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
	int			start_draw;
	int			end_draw;
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
	int			nb_objs;
	double		wdist;
	int			sidew;
	int			lineh;
	int			start_draw;
	int			end_draw;
	t_line		*objs;
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

struct					s_limit
{
	int				xmin;
	int				xmax;
	int				ymin;
	int				ymax;
};

struct					s_minimap
{
	t_point		origin;
	t_point		centre;
	t_point		map_size;
	double		mnp_size;
	t_point		pos_play;
	t_limit		limit;
	t_point		diff;
};

/*
** Gameplay structures
** 1 - Objects
** 2 - Weapons
** 3 - Actions
** 4 - Inventory
** 5 - Character
*/

struct					s_object
{
	SDL_Surface	*sprite;
	int			is_consumable;
	int			nb_use;
};

struct					s_wall
{
	SDL_Surface	*sprite;
	int			health;
	int			height;
	int			width;
	double		angle;
};

struct					s_weapon
{
	SDL_Surface	*sprite;
	SDL_Surface	*sprite_bullet;
	SDL_Surface	**sprite_reload;
	SDL_Surface	**sprite_shoot;
	int			type;
	int			time_reload;
	int			time_shoot;
	double		time_shoot_between;
	int			ammo_current;
	int			ammo_magazine;
	int			ammo_max;
	int			damage;
};

struct					s_world
{
	t_weapon	armory[WORLD_NB_WEAPONS];
	t_object	objects[WORLD_NB_OBJECTS];
	t_wall		walls[WORLD_NB_WALLS];
};

struct					s_action
{
	int			is_shooting;
	int			is_loading;
	int			is_swimming;
	int			is_flying;
	int			is_jumping;
	int			is_up_down;
};

struct					s_inventory
{
	t_weapon	*current;
	t_weapon	weapons[15];
	t_object	objects[15];
};

struct					s_character
{
	int			health;
	int			shield;
	int			max_health;
	int			max_shield;
	int			max_weapons;
	int			max_objects;
	t_point		pos;
	t_point		plane;
	t_point		dir;
	t_action	actions;
	t_inventory	inventory;
	SDL_Surface	*sprite;
};

struct					s_iline
{
	int			x;
	int			y;
	int			delim;
	t_line		line;
	Uint32		color;
};

struct					s_env
{
	SDL_Surface	*ak_frms[43];
	SDL_Surface	*bul_surf[6];
	SDL_Surface	*floor;
	SDL_Surface	*gun_impact;
	SDL_Surface	*mitra_frms[36];
	SDL_Surface	*sky;
	SDL_Surface	*stitch[18];
	SDL_Surface	*walls[10];

	double		ang;
	double		cam;
	double		hratio;
	double		is_updn;
	double		angle_d;
	double		angle_r;

	int			**w_map;
	int			**w_map_2;
	int			height;
	int			width;

	t_character	enemies[10];
	t_minimap	minimap;
	t_hub		life;
	t_hub		lscreen;
	t_hub		title;
	t_msc		sounds;

	t_character player;
	t_point		pos;

	int			is_jump;
	int			is_shootin;
	int			ld_wp;

	t_point		mouse;
	t_sdl		sdl;
	t_thr		thr[THREAD_NBR];
	t_wobj		wobj;
	t_iline		rays[WIDTH];
};

#endif
