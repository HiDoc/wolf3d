/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:34:48 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 16:34:51 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t sizes1;

	i = 0;
	sizes1 = ft_strlen(s1);
	while (i < n && s2[i])
	{
		s1[sizes1] = s2[i];
		sizes1++;
		i++;
	}
	s1[sizes1] = '\0';
	return (s1);
}
