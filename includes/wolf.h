/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2018/08/29 12:36:57 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "wolf_define.h"
# include "wolf_struct.h"

int		wolf(t_env *env);

void	print_error(int nb, t_env *env);
void	free_env(t_env *env);

int		exit_wolf(t_env *env);
int		key_hook(int key, t_env *env);
#endif
