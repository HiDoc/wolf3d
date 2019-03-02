/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_struct_env.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/02 13:06:52 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_STRUCT_ENV_H
# define DOOM_STRUCT_ENV_H

typedef struct s_env				t_env;
typedef struct s_sdl				t_sdl;
typedef struct s_msc				t_msc;

struct					s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Surface		*surface;
	SDL_Event		event;
};

struct					s_msc
{
	Mix_Music		*load;
	Mix_Chunk		*shot;
};

struct					s_env
{
	int				map_w;
	int				map_h;
	t_msc			sounds;
	t_character 	player;
	t_world			world;
	t_sdl			sdl;
	t_engine		engine;
};

#endif
