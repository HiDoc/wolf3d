/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_init.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:52:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/10 23:49:19 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_INIT_H
# define DOOM_F_INIT_H

void		init_env(int ac, char **av, t_env *env);

void		load_fonts(t_env *env);
void		load_images(t_env *env);
void		init_strings(t_env *env, int i, int j);

void		init_hud(t_env *env);
void		init_weapon(t_env *env);
void		init_enemies(t_env *env, t_brain b, int i);

#endif
