/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:49:04 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 15:49:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t		len;
	size_t		lens1;
	size_t		lens2;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (lens1 >= lens2)
		len = lens1;
	else
		len = lens2;
	return (ft_memcmp(s1, s2, len));
}
