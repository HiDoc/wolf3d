/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/09 00:26:18 by sgalasso         ###   ########.fr       */
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
typedef struct	s_msc				t_msc;
typedef struct	s_time				t_time;
typedef struct	s_tiletab			t_tiletab;

struct								s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Surface		*surface;
	SDL_Event		event;
	Uint8			*keycodes;
};

struct								s_msc
{
	Mix_Music		*load;
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

struct								s_env
{
	int				map_w;
	int				map_h;
	t_time			time;
	t_msc			sounds;
	t_character		player;
	t_world			world;
	t_sdl			sdl;
	t_engine		engine;
	t_hud			hud;
	t_stats			stats;
	t_tiletab		tiletab;
	int				god_mod;
	//
	// ...
	//
	// Comment je penses que ce serait mieux :
	//
	// t_sdl			sdl; 		(trucs sdl ...)
	// t_ressources		ressources; (audio / images / fonts ...)
	// t_player			player; 	(pos / health / stats ...)
	// t_level			level; 		(map / entitee ...)
	// t_hud			hud; 		(inventory / minimap / ...)
};

void			doom_exit(void);
void			doom_error_exit(char *str);
void			srf_del(void **ap);	// del surface
void			wdw_del(void **ap); // del window
void			rdr_del(void **ap); // del renderer 
void			txr_del(void **ap); // del texture
void			crs_del(void **ap); // del cursor


void			load_tilesets(t_env *env);

int				init_thread(t_weapon *mother, t_bloc *child, char *path, int size);
int				current_sprite(t_bloc *bloc, char *file, int i);
int				thread_current_sprite(t_bloc *child, char *path, int line, int size);

void			no_op(t_env *env);
int				sdl_render(t_env *env, void (*f)(t_env *env));
int				sdl_loop(t_env *env);

SDL_Surface		*new_surface(char *filename);
void			setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32			getpixel(SDL_Surface *surface, int x, int y);
void			projection_print(t_raycast container);
void			print_edg(t_edge edge);
#endif
