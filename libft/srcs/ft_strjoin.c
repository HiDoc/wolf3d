/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:14:12 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/08 14:09:44 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	count;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if ((new = (char *)malloc(s1len + s2len + 1)) == NULL)
		return (NULL);
	count = 0;
	while (s1[count])
	{
		new[count] = s1[count];
		count++;
	}
	count = 0;
	while (s2[count])
	{
		new[s1len + count] = s2[count];
		count++;
	}
	new[s1len + s2len] = '\0';
	return (new);
}
