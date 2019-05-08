/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 21:37:58 by sgalasso         ###   ########.fr       */
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
typedef struct	s_level				t_level;

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

struct								s_level
{
	int				index;
	Uint32			tplay;
	char			*text;
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
	int				curr_lvl;	// level courant
	int				nb_games;	// nb worlds
	char			**games;	// all worlds
	int				nb_levels;	//nb world levels
	t_level			**levels;	// world levels
	int				finish;		// flag fin de level
};


// a rander dans un header fonctions

void			free_map(t_env *env);

SDL_Surface		*make_surface(int height, int width);
SDL_Surface		*make_string(t_font str_data);
SDL_Surface		*load_image(char *path);

void			no_op(t_env *env);
int				sdl_loop(t_env *env);
void			mainmenu_loop(t_env *env);

void			setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32			getpixel(SDL_Surface *surface, int x, int y);
void			projection_print(t_raycast container);
void			print_edg(t_edge edge);

#endif
