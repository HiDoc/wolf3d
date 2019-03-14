/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:31:34 by sgalasso          #+#    #+#             */
/*   Updated: 2018/04/07 17:42:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s)
	{
		i = 0;
		if (!(str = (char *)(ft_memalloc(sizeof(char) * (len + 1)))))
			return (0);
		while (i < len)
		{
			str[i] = s[start];
			start++;
			i++;
		}
		return (str);
	}
	return (0);
}
