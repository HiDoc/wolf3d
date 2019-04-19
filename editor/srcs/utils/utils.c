/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:48:56 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 00:59:33 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_pos			get_edge_center(t_pos a, t_pos b)
{
	t_pos	center;

	center.x = (a.x + b.x) / 2;
	center.y = (a.y + b.y) / 2;
	return (center);
}

static t_pos   diff_vertex(t_pos p1, t_pos p2)
{
	return ((t_pos){p1.x - p2.x, p1.y - p2.y});
}

static float   cross_product(t_pos p1, t_pos p2)
{
	return (p1.x * p2.y - p2.x * p1.y);
}

/*
** Determine which side of a line the point is on.
** Return value: left < 0, on line 0, right > 0.
*/

float		pointside(t_pos p, t_pos p0, t_pos p1)
{
	return (cross_product(diff_vertex(p1, p0), diff_vertex(p, p0)));
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

float	pythagore(t_pos p1, t_pos p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
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
