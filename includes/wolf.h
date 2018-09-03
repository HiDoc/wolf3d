/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/03 17:24:47 by fmadura          ###   ########.fr       */
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

void	img(t_env *env);
int		line_floor(t_env *env, t_line *line, int y);
int		line_wall(t_env *env, t_line *line, int y);
int		line_sky(t_env *env, t_line *line, int y);
t_line	*line_init(t_env *env, t_line *line, int x);
t_line	*line_dda(t_env *env, t_line *line);
t_line	*line_step(t_env *env, t_line *line);
t_line	*line_max(t_env *env, t_line *line);
int		motion_mouse(int x, int y, t_env *env);
int		init_thread(t_env *env);
#endif
