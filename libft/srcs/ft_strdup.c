/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:32:10 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/08 23:56:40 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*dup;
	int		count;

	count = 0;
	len = ft_strlen(s1);
	dup = (char *)ft_memalloc(sizeof(char) * (len + 1));
	while (count < len)
	{
		dup[count] = s1[count];
		count++;
	}
	dup[count] = s1[count];
	return (dup);
}
