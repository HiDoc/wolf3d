/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:30:35 by abaille           #+#    #+#             */
/*   Updated: 2019/04/08 23:59:36 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	i;
	char	*ptr;

	if (s)
	{
		i = 0;
		ptr = (char*)ft_memalloc(sizeof(*ptr) * (ft_strlen(s) + 1));
		while (s[i])
		{
			ptr[i] = f(s[i]);
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	else
		return (NULL);
}
