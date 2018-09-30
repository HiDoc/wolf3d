/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/25 11:46:06 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "wolf_define.h"
# include "wolf_struct.h"

int			wolf(t_env *env, int col);

void		print_error(int nb, t_env *env);

void		free_env(t_env *env);

int			exit_wolf(t_env *env);

int			key_hook(int key, t_env *env);

void        put_health(t_env *env);
void		put_gun(t_env *env);
void		img(t_env *env);

int			ft_sqr(int a);
int			ft_pyt(int a, int b);

int			line_floor(t_env *env, t_line *line, int y);
int			line_wall(t_env *env, t_line *line, int y);
int			line_sky(t_env *env, t_line *line, int y);

t_line		*objs_init(t_env *env, t_line *line, int x, int **tab);
t_line		*objs_dda(t_env *env, t_line *line, int **tab);
t_line		*objs_step(t_env *env, t_line *line, int **tab);
t_line		*objs_max(t_env *env, t_line *line);

t_line		*line_init(t_env *env, t_line *line, int x);
t_line		*line_dda(t_env *env, t_line *line);
t_line		*line_step(t_env *env, t_line *line);
t_line		*line_max(t_env *env, t_line *line);

t_ray		*ray_init(t_env *env, t_ray *ray, int x);
t_ray		*ray_dda(t_env *env, t_ray *ray);
t_ray		*ray_step(t_env *env, t_ray *ray);
t_ray		*ray_max(t_env *env, t_ray *ray);

t_point		portal_pos(t_env *env, t_point pos);

int			motion_mouse(int x, int y, t_env *env);
int			init_thread(t_env *env);
int			init_env(t_env *env);
void		init_sdl(t_env *env);
int			fill_tab(t_env *env);

void        launch_screen(t_env *env);
void    	turn_logo(t_env *env);

void		copy_sdl(t_env *env);
void	    health(t_env *env);
void    	hub_texture(t_env *env, t_hub *bloc, char *line, char *police);
SDL_Surface	*surface_new(Uint32 *pixels, int width, int height);
void		surface_set_pixel(SDL_Surface *s, SDL_Color c, size_t x, size_t y);
int			sdl_keyhook(t_env *env, SDL_Event event);
int			sdl_motion_mouse(t_env *env, int x, int y);

t_img       *img_new(t_env *env, char *filename);

int			**tab_copy(int **src, int **dest, int x, int y);
int			**tab_set(int **src, int x, int y, int val);
int			**tab_init(int **src, int x, int y);
int			tab_free(int **tab, int y);
#endif
