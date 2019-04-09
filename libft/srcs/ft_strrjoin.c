/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:13:04 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/09 14:56:51 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrjoin(char *s1, char *s2)
{
	char	*new;

	new = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		new = ft_strjoin(s1, s2);
		lt_release(s2);
	}
	return (new);
}
