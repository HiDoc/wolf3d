/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 21:48:26 by sgalasso          #+#    #+#             */
/*   Updated: 2018/04/04 13:39:34 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		temp = i;
		while (needle[j] && haystack[temp] == needle[j] && temp < len)
		{
			temp++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + temp - j);
		i++;
	}
	return (0);
}
