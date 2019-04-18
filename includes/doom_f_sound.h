/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_sound.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:30:51 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 02:58:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_SOUND_H
# define DOOM_F_SOUND_H

void			init_sounds(t_env *e);
void			set_msc_menu(t_env *e, t_status *s);
void			menu_btn_sound(t_env *e, const Uint8 *k);
void			sound_player(t_env *e, t_player *p);
unsigned int	sound_rand(int max);
#endif