/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_init.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:52:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 22:32:25 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_INIT_H
# define DOOM_F_INIT_H

void		initialisation(int ac, char **av, t_env *env);

void		load_fonts(t_env *env);
void		load_images(t_env *env);
int			init_strings(t_env *env, int i, int j);

int			init_hud(t_env *env);
int			init_weapon(t_env *env);
int			init_enemies(t_env *env);

#endif
