/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:32:10 by fmadura           #+#    #+#             */
/*   Updated: 2017/11/11 13:44:23 by fmadura          ###   ########.fr       */
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
	dup = (char*)malloc(((sizeof(char) * len) + 1));
	if (dup == NULL)
		return (NULL);
	while (count < len)
	{
		dup[count] = s1[count];
		count++;
	}
	dup[count] = s1[count];
	return (dup);
}
