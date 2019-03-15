/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:34:39 by sgalasso          #+#    #+#             */
/*   Updated: 2018/10/17 11:54:32 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_getnbwords(char *str, char c)
{
	int i;
	int cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			cpt++;
		else if (i != 0 && str[i] != c && str[i - 1] == c)
			cpt++;
		i++;
	}
	return (cpt);
}

char			**ft_strsplit(char const *str, char c)
{
	int		i;
	int		start;
	int		end;
	int		index;
	char	**dest;

	i = 0;
	index = 0;
	if (!str || !(dest = (char **)(ft_memalloc(sizeof(char *)
	* (ft_getnbwords((char *)str, c) + 1)))))
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		start = i;
		while (str[i] && str[i] != c)
			i++;
		end = i;
		if (end > start)
			if (!(dest[index++] = ft_strsub(str, start, end - start)))
				return (0);
	}
	return (dest);
}
