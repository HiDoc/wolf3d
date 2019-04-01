/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:48:56 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/30 13:15:10 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
	if (s1)
		str = ft_strcat(str, s1);
	if (s2)
		str = ft_strcat(str, s2);
	return (str);
}
