/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2018/12/27 19:43:40 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "wolf_define.h"
# include "wolf_struct.h"

void		parse_map(t_env * env, char *filename);

int			wolf(t_env *env, int col);
int			tron(t_env *env, int col);
void		print_error(int nb, t_env *env);
void		free_env(t_env *env);
int			exit_wolf(t_env *env);
int			key_hook(int key, t_env *env);
int			render_env(t_env *env);

void		put_health(t_env *env);
void		put_gun(t_env *env);
void		put_gun_load(t_env *env, int frame);
void		img(t_env *env);

double		delta(double x, double y);
double		dist(double map, double pos, double step, double ray);
double		ldist(t_env *env, t_line *line, char side);

Uint32		line_floor(t_env *env, t_line *line, int y);
Uint32		line_floor_under(t_env *env, t_line *line, int y);
Uint32		line_wall(t_env *env, t_line *line, int y);
Uint32		line_wall_2(t_env *env, t_line *line, int y);
Uint32		line_sky(t_env *env, t_line *line, int y);
Uint32		line_sky_infinite(t_env *env, t_line *line, int y);
t_point		*get_fwall(t_line *line, t_point *fwall);

Uint32		line_tron_floor(t_env *env, t_line *line, int y);
Uint32		line_tron_wall(t_env *env, t_line *line, int y);
Uint32		line_tron_ceil(t_env *env, t_line *line, int y);

t_line		*obj_init(t_env *env, t_line *line);

t_line		*line_init(t_env *env, t_line *line, int **map, int x);
t_line		*line_dda(t_env *env, t_line *line, int **map);
t_line		*line_step(t_env *env, t_line *line, int **map);
t_line		*line_max(t_env *env, t_line *line);

t_point		*point_cpy(t_point *a, t_point *b);
t_point		*point_delta(t_point *a, t_point *b);
t_point		*point_ray(t_point *a, t_point *b, t_point *c, double cam);
t_point		point_rotate(t_point v, int angle);
t_point		portal_pos(t_env *env, t_point pos);
void		point_set(t_point *a, double x, double y);
void		point_diff(t_point *a, t_point b, t_point c);

int			wall_fog(t_env *env, t_line *line, Uint32 c, int y);
int			sky_fog(t_env *env, t_line *line, Uint32 c, int y);
int			floor_fog(t_env *env, t_line *line, Uint32 c, int y);

int			motion_mouse(int x, int y, t_env *env);
int			init_thread(t_env *env, int threads);
int			init_env(t_env *env, char *filename);
int			env_free(t_env *env);
void		init_sdl(t_env *env);
int			fill_tab(t_env *env);
void		tab_print(int **tab, int x, int y);

void		launch_screen(t_env *env);
void		turn_logo(t_env *env);

void		copy_sdl(t_env *env);
void		health(t_env *env);
void		hub_texture(t_env *env, t_hub *bloc, char *line, char *police);
int			sdl_keyhook(t_env *env, SDL_Event event);
int			sdl_motion_mouse(t_env *env, int x, int y);
int			sdl_mouse_click(t_env *env, int x, int y);
int			sdl_exit_wolf(t_env *env, Uint8 scancode);
void        ui_put_string(t_env *env, char *str, int x, int y);
void        ui_put_fps(t_env *env, int fps);
void	    put_img(t_env *env, SDL_Surface *img, int x, int y);
void	    put_enemy(t_env *env);

SDL_Surface	*surface_new(Uint32 *pixels, int width, int height);
SDL_Surface	*img_new(char *filename);

Uint32		getpixel(SDL_Surface *surface, int x, int y);
void		setpixel(SDL_Surface *s, int x, int y, Uint32 color);
void	    surface_drawline(SDL_Surface *surface,
			t_point start, t_point end, Uint32 color);
void		surface_drawline_limit(SDL_Surface *surface,
			t_point start, t_point end, t_limit limit, Uint32 color);
void		surface_drawrect(SDL_Surface *surface,
			SDL_Rect rect, t_limit *limit, Uint32 color);
void        surface_drawborder(SDL_Surface *surface,
			SDL_Rect rect, Uint32 color);

void		tab_copy(int **src, int **dest, int x, int y);
int			**tab_copy_alloc(int **src, int x, int y);
int			**tab_init(int **src, int x, int y);
int			tab_free(int **tab, int y);

void		load_sounds(t_env *env);

int			put_poster(t_env *env);
int			wall_poster(t_env *env, t_line *line);
int			wall_impact(t_env *env);
int			check_impact(t_line *line, t_env *env);
int			affiche_map(t_env *env, Uint8 keycode);
int			load_weapon(t_env *env, Uint8 keycode, SDL_Surface **weapon);
int			shoot_weapon(t_env *env, int frame);
int			player_jump(t_env *env);

/*
** display minimap
*/

void		struct_minimap(t_env *env);

#endif
