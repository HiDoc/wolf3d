/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:47:49 by abaille           #+#    #+#             */
/*   Updated: 2019/05/02 17:41:35 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_MENU_H
# define DOOM_S_MENU_H

typedef	struct s_menu		t_menu;
typedef	struct s_status		t_status;

struct 			s_status
{
	int			on;
	int			home;
	int			main_menu;
	int			load_menu;
	int			ingame;
	int			options_menu;
	int			new_game;
	int			gameover;
	int			quit;
	int			nb_save;
	int			cur;
	int			key_change;
	int			sound;
	int			msc_vol;
	int			start;
	int			end;
	int			inter;

};

struct 			s_menu
{
	t_status	status;
	t_bloc		main_menu[NB_BL_NG]; // buttns menu
	t_bloc		ingame_menu[NB_BLOC_IG]; // buttns ingame_menu menu
	t_bloc		options_menu[NB_OPT_MENU]; // buttns options // keys options to change keys
	t_bloc		load_menu;
	t_bloc		*save; // list chain 1 bloc = save img + time
	t_bloc		new_game;
	t_bloc		inter;
};


#endif