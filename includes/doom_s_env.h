/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/21 13:06:18 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_ENV_H
# define DOOM_S_ENV_H

typedef struct s_env				t_env;
typedef struct s_sdl				t_sdl;
typedef struct s_msc				t_msc;
typedef struct s_time				t_time;
typedef struct s_ui					t_ui;

struct								s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Surface		*surface;
	SDL_Event		event;
};

struct								s_msc
{
	Mix_Music		*load;
};

struct s_time
{
	int				fps;
	Uint32			time_a;
	Uint32			time_b;
	int				frame;
	int				tframe;
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
	t_ui			ui;

	// font sgalasso, a ranger je sais pas ou
	TTF_Font		*arial_font;
};

void			no_op(t_env *env);
int				sdl_render(t_env *env, void (*f)(t_env *env));
int				sdl_loop(t_env *env);
int				init_container(t_env *env);

SDL_Surface		*new_surface(char *filename);
void			setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32			getpixel(SDL_Surface *surface, int x, int y);
void			projection_print(t_raycast container);
void			print_edg(t_edge edge);
#endif
