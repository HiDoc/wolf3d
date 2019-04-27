/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_ptr_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:09:27 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 20:09:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		right_upper(t_tga *data)
{
	return (data->width * data->i + (data->width - data->j - 1));
}

int		right_lower(t_tga *data)
{
	return (pos = data.width * (data.height - data.i - 1)
		+ (data.width - data.j - 1));
}

int		left_upper(t_tga *data)
{
	return (data.width * data.i + data.j);
}

int		left_lower(t_tga *data)
{
	return (data.width * (data.height - data.i - 1) + data.j);
}