/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:48:56 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/27 18:35:17 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_dropdown_list(SDL_Rect rect, t_elem *elem,
			int index, t_env *env)
{
	Uint32		color;
	SDL_Rect	box;

	while (elem)
	{
		color = (elem->clicked == 1) ? C_GREEN : C_WHITE;
		box = (SDL_Rect){elem->rect.x, elem->rect.y + index * 40,
		elem->rect.w, elem->rect.h};
		if (box.y >= rect.y && box.y <= rect.y + rect.h)
		{
			ui_make_rect(env->data->surface, box, color);
			ui_make_string(box, elem->str, env->data);
		}
		elem = elem->next;
	}
}

void		display_error_msg(char *msg, t_env *env)
{
	if (env->editor.error_msg)
		lt_release(env->editor.error_msg);
	env->editor.timestamp = time(0);
	if (!(env->editor.error_msg = lt_push(ft_strdup(msg), ft_memdel)))
		ui_error_exit_sdl("Editor: out of memory on delete_vertex");
}

t_pos		vtx_transform(t_pos pos, t_env *env)
{
	const SDL_Rect  rect = get_element(E_R_RECT, env)->rect;
	t_pos           newpos;
	t_pos			translate;
	t_pos			origin;

	origin.x = rect.x + 425;
	origin.y = rect.y + 340;

	translate.x = env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	translate.y = env->editor.grid_translate.y + env->editor.grid_mouse_var.y;

	newpos.x = origin.x + (pos.x + translate.x) * env->grid_scale;
	newpos.y = origin.y + (pos.y + translate.y) * env->grid_scale;
	return (newpos);
}

t_w_vtx		*w_vtx_lst_end(t_w_vtx *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_sct		*sct_lst_end(t_sct *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void			sync_sct_minmax(t_env *env)
{
	t_sct		*sct;
	t_w_vtx		*w_vtx;

	sct = env->sct_start;
	while (sct)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx)
		{
			(w_vtx->vtx->pos.x < sct->xmin) ? sct->xmin = w_vtx->vtx->pos.x : 0;
			(w_vtx->vtx->pos.x > sct->xmax) ? sct->xmax = w_vtx->vtx->pos.x : 0;
			(w_vtx->vtx->pos.y < sct->ymin) ? sct->ymin = w_vtx->vtx->pos.y : 0;
			(w_vtx->vtx->pos.y > sct->ymax) ? sct->ymax = w_vtx->vtx->pos.y : 0;
			w_vtx = w_vtx->next;
		}
		sct = sct->next;
	}
}

float	pythagore(t_pos p1, t_pos p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

t_pos			get_edge_center(t_pos a, t_pos b)
{
	t_pos	center;

	center.x = (a.x + b.x) / 2;
	center.y = (a.y + b.y) / 2;
	return (center);
}

/*
** Determine which side of a line the point is on.
** Return value: left < 0, on line 0, right > 0.
*/

float		pointside(t_pos p, t_pos p0, t_pos p1)
{
	t_pos	res1;
	t_pos	res2;
	float	res;

	res1 = (t_pos){p1.x - p0.x, p1.y - p0.y};
	res2 = (t_pos){p.x - p0.x, p.y - p0.y};
	res = res1.x * res2.y - res2.x * res1.y;
	return (res);
}

/*
** return : 1 if string not empty, 0 if str is empty
*/

int		input_add(int elem, char *key, t_env *env)
{
	char *tmp;

	if (get_element(elem, env)->str_max == 0)
	{
		tmp = get_element(elem, env)->str;
		if (!(get_element(elem, env)->str =
		lt_push(ft_zstrjoin(get_element(elem, env)->str, key), ft_memdel)))
			ui_error_exit_sdl("Editor: Out of memory");
		lt_release(tmp);
		return (1);
	}
	return (0);
}

/*
** return : 1 if last char has been deleted, 0 if str is now empty
*/

int		input_del(int elem, t_env *env)
{
	int		newsize;

	newsize = 0;
	if (get_element(elem, env)->str)
	{
		newsize = ft_strlen(get_element(elem, env)->str) - 1;
		if (newsize > 0)
			get_element(elem, env)->str[newsize] = 0;
		else
		{
			lt_release(get_element(elem, env)->str);
			return (0);
		}
	}
	return (1);
}

int		ft_strchri(char *str, char c)
{
	int count;

	count = 0;
	while (str[count])
	{
		if (str[count] == c)
			return (count);
		count++;
	}
	return (-1);
}

int		poscmp(t_pos a, t_pos b)
{
	return (a.x == b.x && a.y == b.y);
}

char	*ft_zstrjoin(char *s1, char *s2)
{
	char	*str;
	int		size;

	size = 0;
	if (!s1 && !s2)
		return (0);
	(s1) ? size = ft_strlen(s1) : 0;
	(s2) ? size += ft_strlen(s2) : 0;
	if (!(str = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return (0);
	(s1) ? str = ft_strcat(str, s1) : 0;
	(s2) ? str = ft_strcat(str, s2) : 0;
	return (str);
}
