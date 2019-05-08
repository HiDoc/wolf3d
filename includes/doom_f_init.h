/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_init.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:52:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 20:40:44 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_INIT_H
# define DOOM_F_INIT_H

void		init_env(int ac, char **av, t_env *env);
void		init_rsrc(t_env *e);
int			draw_end_loadin(t_env *e, int i, TTF_Font *font, SDL_Rect r);

void		ld_fonts(t_env *env);
void		ld_img(t_env *env);
void		init_strings(t_env *env, int i);

void		init_hud(t_env *env);
void		init_igems_bloc(t_uinv *inventory, t_container *surfaces);
void		init_icon_bloc(t_uinv *inventory, t_container *surfaces);
void		init_iwpn_bloc(t_uinv *inventory, t_container *surfaces);
void		init_iobjects_bloc(t_env *env, t_uinv *inventory);

void		init_weapon(t_env *env);
void		init_enemies(t_env *env, t_brain b, int i);

void		underscore_off_name(char *name, int size);

#endif
