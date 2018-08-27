/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:31:26 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 16:31:27 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptr;

	if (s)
	{
		i = 0;
		ptr = (char*)malloc(sizeof(*ptr) * (ft_strlen(s) + 1));
		if (!ptr)
			return (NULL);
		while (s[i])
		{
			ptr[i] = f(i, s[i]);
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	else
		return (NULL);
}
