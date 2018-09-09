/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/07 16:35:06 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "wolf_define.h"
# include "wolf_struct.h"

int		wolf(t_env *env, int col);

void	print_error(int nb, t_env *env);

void	free_env(t_env *env);

int		exit_wolf(t_env *env);

int		key_hook(int key, t_env *env);

void	put_gun(t_env *env);
void	img(t_env *env);

double	ft_sqr(double a);
double	ft_pyt(double a, double b);
double	ft_delta(double a, double b);

int		line_floor(t_env *env, t_line *line, int y);
int		line_wall(t_env *env, t_line *line, int y);
int		line_sky(t_env *env, t_line *line, int x, int y);

t_line	*line_init(t_env *env, t_line *line, int x);
t_line	*line_dda(t_env *env, t_line *line);
t_line	*line_step(t_env *env, t_line *line);
t_line	*line_max(t_env *env, t_line *line);

t_ray	*ray_init(t_env *env, t_ray *ray, int x);
t_ray	*ray_dda(t_env *env, t_ray *ray);
t_ray	*ray_step(t_env *env, t_ray *ray);
t_ray	*ray_max(t_env *env, t_ray *ray);

t_point	portal_pos(t_env *env, t_point pos);

int		motion_mouse(int x, int y, t_env *env);
int		init_thread(t_env *env);
int		init_env(t_env *env);
int		fill_tab(t_env *env);
#endif
