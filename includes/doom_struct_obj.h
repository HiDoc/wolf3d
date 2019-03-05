#include "doom.h"

#ifndef DOOM_STRUCT_OBJ_H
# define DOOM_STRUCT_OBJ_H

typedef struct s_wrap_inv		t_wrap_inv;
typedef struct s_wrap_sect      t_wrap_sect;
typedef struct s_actions        t_actions;
typedef struct s_uinv	        t_uinv;

struct 					s_uinv
{
	SDL_Surface	*front_pic;
	int			is_active;
	t_edge		blocs[6];
	int			wwheel;
	int			nb_wpn;
};


struct                  s_actions
{
    int         is_shield;
    int         is_health;
    int         is_ammo;
	int			sub_action;
	t_edge		edge;
	int			is_shooting;
	int			is_loading;
};

struct					s_wrap_sect
{
	t_vtx		vertex;
	int			is_picked;
	int			ref;
    int         (*action)(void *, t_wrap_inv *);
	t_wrap_sect	*next;
};


struct					s_wrap_inv
{
	t_wrap_sect		*current;
	int				nb_stack;
    int             is_used;
	t_edge			udbox[2];
	SDL_Surface		*curr_img;
	t_ixy			mmotion;
	int				is_dragged;
	t_edge			where_img;
};

#endif