/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:09:27 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 17:46:44 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		right_upper(t_tga *d)
{
	return (d->width * d->i + (d->width - d->j - 1));
}

int		right_lower(t_tga *d)
{
	return (d->width * (d->height - d->i - 1) + (d->width - d->j - 1));
}

int		left_upper(t_tga *d)
{
	return (d->width * d->i + d->j);
}

int		left_lower(t_tga *d)
{
	return (d->width * (d->height - d->i - 1) + d->j);
}

void	*get_ft_index(t_tga *data)
{
	if (data->descriptor & RIGHT_ORIGIN)
	{
		if (data->descriptor & UPPER_ORIGIN)
			return (&right_upper);
		else
			return (&right_lower);
	}
	else
	{
		if (data->descriptor & UPPER_ORIGIN)
			return (&left_upper);
		else
			return (&left_lower);
	}
	return (NULL);
}