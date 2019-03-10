#include "doom.h"

#ifndef DOOM_STRUCT_OBJ_H
# define DOOM_STRUCT_OBJ_H

typedef struct s_wrap_inv		t_wrap_inv;
typedef struct s_wrap_wpn		t_wrap_wpn;
typedef struct s_wrap_sect      t_wrap_sect;
typedef struct s_actions        t_actions;
typedef struct s_uinv	        t_uinv;
typedef struct s_hud			t_hud;

struct					s_hud
{
	SDL_Surface			*empty_bar;
	SDL_Surface			*bar[2];
	SDL_Surface			*hud_wpn[3];
	SDL_Surface			*pad;
	SDL_Surface			*shadow;
	SDL_Surface			*e_pad[4];
	t_wrap_inv			*shortcut[6];
	int					is_txt;
};

struct 					s_uinv
{
	SDL_Surface	*front_pic;
	SDL_Surface	*mini_wpn[3];
	SDL_Surface	*empt_wpn[3];
	SDL_Surface	*icon[3];
	SDL_Surface	*box[2];
	SDL_Color	color;
	t_edge		blocs[6];
	t_edge		wblocs[3];
	t_edge		iblocs[3];
	int			is_active;
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
	int			is_flying;
};

struct					s_wrap_sect
{
	t_vtx		vertex;
	int			is_picked;
	int			ref;
	int			is_wpn;
    int         (*action)(void *, t_wrap_inv *);
	t_wrap_sect	*next;
};

struct					s_wrap_inv
{
	t_wrap_sect		*current;
	int				nb_stack;
    int             is_used;
	t_edge			udbox[2];
};

struct					s_wrap_wpn
{
	t_wrap_sect		*current;
	int				ammo_current;
	int				ammo_magazine;
};

#endif