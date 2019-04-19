/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/17 19:28:34 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_ENV_H
# define DOOM_S_ENV_H

enum								e_tileset
{
	ENUM_0,
	ENUM_1,
	ENUM_2,
	ENUM_3,
	ENUM_4,
	ENUM_5,
	ENUM_6,
	ENUM_7,
	ENUM_8,
	ENUM_9,
	ENUM_10,
	ENUM_11,
	ENUM_12,
	ENUM_13,
	ENUM_14,
	ENUM_15,
	ENUM_16,
	ENUM_17,
	ENUM_18,
	ENUM_19
};

typedef struct	s_env				t_env;
typedef struct	s_sdl				t_sdl;
typedef struct	s_time				t_time;
typedef struct	s_tiletab			t_tiletab;
typedef struct	s_skybox			t_skybox;

struct								s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Surface		*surface;
	SDL_Event		event;
	Uint8			*keycodes;
};

struct 								s_time
{
	int				fps;
	Uint32			time_a;
	Uint32			time_b;
	int				frame;
	int				tframe;
	int				t_blue;
	int				t_green;
	int				t_red;
	int				t_purple;
};

struct								s_tiletab
{
	char			*path;
	SDL_Surface		*tileset;
	int				nb_column;
	int				nb_tiles;
	int				tile_size;
	SDL_Surface		**surface;
};

struct								s_skybox
{
	SDL_Surface		*sb_top;
	SDL_Surface		*sb_front;
	SDL_Surface		*sb_right;
	SDL_Surface		*sb_back;
	SDL_Surface		*sb_left;

	SDL_Surface		*sb;
};

struct								s_env
{
	int				map_w;
	int				map_h;
	t_time			time;
	t_sound			sound;
	t_character		player;
	t_world			world;
	t_sdl			sdl;
	t_engine		engine;
	t_hud			hud;
	t_stats			stats;
	t_menu			menu;
	int				god_mod;
	t_tiletab		tiletab;

	/* skybox */
	t_skybox		skybox;

	// Comment je penses que ce serait mieux :
	//
	// t_sdl			sdl; 		(trucs sdl ...)
	// t_ressources		ressources; (audio / images / fonts ...)
	// t_player			player; 	(pos / health / stats ...)
	// t_level			level; 		(map / entitee ...)
	// t_hud			hud; 		(inventory / minimap / ...)
};


// a rander dans un header fonctions
void			doom_exit(void);
void			doom_error_exit(char *str);
void			srf_del(void **ap);	// del surface
void			wdw_del(void **ap); // del window
void			rdr_del(void **ap); // del renderer
void			txr_del(void **ap); // del texture
void			crs_del(void **ap); // del cursor
void			ttf_del(void **ap); // del ttf font

void			display_skybox(t_env *env);

void			load_tilesets(t_env *env);

void			no_op(t_env *env);
int				sdl_loop(t_env *env);

void			setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32			getpixel(SDL_Surface *surface, int x, int y);
void			projection_print(t_raycast container);
void			print_edg(t_edge edge);
#endif
