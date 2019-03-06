/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 15:57:32 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/05 11:51:27 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	projection_print(t_raycast container)
{
	printf("projection: y1{%d, %d}, y2{%d, %d}, {x1 : %d, x2 : %d}\n",
			container.p.y1a, container.p.y1b,
			container.p.y2a, container.p.y2b,
			container.x1, container.x2);
}