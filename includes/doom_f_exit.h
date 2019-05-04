/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_exit.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:18:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/04 19:52:07 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_EXIT_H
# define DOOM_F_EXIT_H

void			doom_exit(void);
void			doom_error_exit(char *str);
void			srf_del(void **ap);	// del surface
void			wdw_del(void **ap); // del window
void			rdr_del(void **ap); // del renderer
void			txr_del(void **ap); // del texture
void			crs_del(void **ap); // del cursor
void			ttf_del(void **ap); // del ttf font
void			msc_del(void **ap); // del mix music
void			chk_del(void **ap); // del mix chunk
void			dir_del(void **ap);

#endif
