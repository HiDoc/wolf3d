/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:47:49 by abaille           #+#    #+#             */
/*   Updated: 2019/04/15 15:12:40 by abaille          ###   ########.fr       */
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
	int			ingame_menu;
	int			options_menu;
	int			quit;
	int			nb_save;
	int			current;
	int			key_change;
	int			sound;
	int			click;
};

struct 			s_menu
{
	t_status	status;
	t_bloc		main_menu[NB_BLOC_NG]; // buttns menu
	t_bloc		ingame_menu[NB_BLOC_IG]; // buttns ingame_menu menu
	t_bloc		options_menu[NB_OPT_MENU]; // buttns options // keys options to change keys
	t_bloc		load_menu;
	t_bloc		*games_ldmenu; // list chain 1 bloc = save img + time
};


#endif