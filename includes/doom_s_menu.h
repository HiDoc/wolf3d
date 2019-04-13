/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:47:49 by abaille           #+#    #+#             */
/*   Updated: 2019/04/13 15:41:59 by abaille          ###   ########.fr       */
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
};

struct 			s_menu
{
	t_status	status;
	t_bloc		mother_menu;

	t_bloc		load_menu; // load game page blocs
	t_bloc		*games_ldmenu; // 1 bloc = save img + time

	t_bloc		main_menu[NB_BLOC_NG]; // buttns menu

	t_bloc		ingame_menu[NB_BLOC_IG]; // buttns ingame_menu menu

	t_bloc		options_menu[NB_OPT_MENU]; // buttns options
	int			keys[NB_OPT_KEY]; // keys options to change keys

	SDL_Surface	*opt_str[NB_OPT_KEY]; // related strings menu
	SDL_Surface	*title[6]; // title page menu
	SDL_Surface	*string[NB_MENU_BTN]; // related strings menu
	SDL_Surface	*hover[NB_HOVER_STR]; // related strings menu
};


#endif