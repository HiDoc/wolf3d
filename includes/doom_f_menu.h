/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:36:24 by abaille           #+#    #+#             */
/*   Updated: 2019/04/19 14:39:40 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_MENU_H
# define DOOM_F_MENU_H

void		init_blocs_menu(t_env *env);
void		draw_menu(t_env *env);
void		action_mainmenu(t_env *e, t_status *s, const Uint8 *k);
void		action_ingame_menu(t_env *e, t_status *s, const Uint8 *k);
void		action_loadmenu(t_env *e, t_status *s, const Uint8 *k);
void		action_optionmenu(t_env *e, t_status *s, const Uint8 *k);
void		change_option(t_env *e, t_status *s, const Uint8 *k, int *key);
int			check_doublon(t_status *s, int scan, int *ktab);
void		scroll_menu(int *cur, const Uint8 *k, int start, int limit);
void		exit_menu(t_env *e, t_status *s, int p);

#endif