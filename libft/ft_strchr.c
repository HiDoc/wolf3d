/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:44:40 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 15:44:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return ((char*)s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char*)s + i);
	return (NULL);
}
