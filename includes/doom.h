/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 14:55:48 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

/*
** Include all define
*/
# include "doom_define.h"
# include "doom_d_ui.h"
# include "doom_d_hud.h"
# include "doom_d_gameplay.h"
# include "doom_d_menu.h"
# include "doom_d_sound.h"

/*
** Include all structures
*/
# include "doom_s_assets.h"
# include "doom_s_math.h"
# include "doom_s_sound.h"
# include "doom_s_wrapper.h"
# include "doom_s_ui.h"
# include "doom_s_hud.h"
# include "doom_s_gameplay.h"
# include "doom_s_menu.h"
# include "doom_s_engine.h"
# include "doom_s_env.h"

/*
** Then include all functions
*/
# include "doom_f_init.h"
# include "doom_f_exit.h"
# include "doom_f_math.h"
# include "doom_f_parser.h"
# include "doom_f_gameplay.h"
# include "doom_f_ui.h"
# include "doom_f_engine.h"
# include "doom_f_hud.h"
# include "doom_f_menu.h"
# include "doom_f_sound.h"

/*
** Include Parsing
*/
#include "ast.h"

#endif
