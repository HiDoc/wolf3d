/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:48:56 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:31:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int				sector_in_rect(t_sct *sct, SDL_Rect rect, t_env *env)
{
	t_w_vtx		*w_vtx;
	t_pos		pos;

	while (sct)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx)
		{
			pos = vtx_transform(w_vtx->vtx->pos, env);
			if (point_in_rect(pos, rect))
				return (1);
			w_vtx = w_vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

t_elem			*get_element_by_ref(int ref, int dd, t_env *env)
{
	t_elem		*elem;

	elem = env->editor.dropdown[dd].start;
	while (elem)
	{
		if (elem->ref == ref)
			return (elem);
		elem = elem->next;
	}
	return (0);
}

t_elem			*get_dd_element(int id, int dd, t_env *env)
{
	t_elem		*elem;
	int			i;

	i = 0;
	elem = env->editor.dropdown[dd].start;
	while (elem && i < id)
	{
		elem = elem->next;
		i++;
	}
	return (elem);
}

int				shared_vtx(t_vtx *vtx, t_sct *current)
{
	t_w_vtx		*w_vtx;

	w_vtx = current->w_vtx_start;
	while (w_vtx)
	{
		if (w_vtx->vtx == vtx)
			return (1);
		w_vtx = w_vtx->next;
	}
	return (0);
}

/*
**	Return 0 if an object is not in a sector
*/

int			refresh_object_sct(t_env *env)
{
	t_object	*obj;
	int			ret;

	ret = 1;
	obj = env->editor.objects;
	while (obj)
	{
		if (!(obj->sct = target_sector(obj->pos, env)))
			ret = 0;
		obj = obj->next;
	}
	return (ret);
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
	newpos.x = origin.x + (pos.x + translate.x) * env->editor.grid_scale;
	newpos.y = origin.y + (pos.y + translate.y) * env->editor.grid_scale;
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

	sct = env->editor.sct_start;
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
		lt_release((void**)&tmp);
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
			lt_release((void**)&get_element(elem, env)->str);
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
