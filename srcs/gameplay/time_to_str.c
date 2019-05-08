/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:49:46 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 12:39:46 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	convert_time(int *hour, int *min, int *sec, Uint32 timems)
{
	timems /= 1000;
	*sec = timems % 60;
	timems /= 60;
	*min = timems % 60;
	timems /= 60;
	*hour = timems;
}

char	*time_to_str(Uint32 times)
{
	char	*name;
	int		hour;
	int		min;
	int		sec;
	char	*t;

	convert_time(&hour, &min, &sec, times);
	t = ft_itoa(hour);
	name = ft_strljoin(t, " h ");
	t = ft_itoa(min);
	name = ft_strljoin(name, t);
	lt_release((void**)&t);
	t = ft_itoa(sec);
	name = ft_strljoin(name, " mn ");
	name = ft_strljoin(name, t);
	name = ft_strljoin(name, " sec");
	lt_release((void**)&t);
	return (name);
}
