/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_sound.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:30:51 by abaille           #+#    #+#             */
/*   Updated: 2019/04/19 14:16:50 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_SOUND_H
# define DOOM_F_SOUND_H

void			init_sounds(t_env *e);
void			set_msc_menu(t_env *e, t_status *s);
void			menu_btn_sound(t_env *e, const Uint8 *k);
void			sd_stat_player(t_engine *e, t_vision *v, t_sd_stat *s);
void			sound_player(t_env *e, t_sd_stat *s);
unsigned int	sound_rand(int max);
void			sound_enemies(t_env *e, t_wrap_enmy *en, t_vtx p);
void			sound_hud(t_env *e, t_sd_stat *s);
void			sound_effect(t_env *e, t_sd_stat *s);
void			handle_sound(t_env *e, t_sd_stat *s);
void			play_chunk(int chan, Mix_Chunk *c, int loop);

#endif