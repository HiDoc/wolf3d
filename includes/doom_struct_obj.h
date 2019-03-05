#include "doom.h"

#ifndef DOOM_STRUCT_OBJ_H
# define DOOM_STRUCT_OBJ_H

typedef struct s_wrap_inv		t_wrap_inv;
typedef struct s_wrap_sect      t_wrap_sect;
typedef struct s_actions        t_actions;

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
};

#endif